#include <d2d1.h>
#include <d2d1helper.h>
#include <wincodecsdk.h>
#include <wrl.h>

#include <memory>
#include <iostream>
#include <string>

using namespace Microsoft::WRL;

ComPtr<IWICImagingFactory> createWICImagingFactory()
{
	ComPtr<IWICImagingFactory> factory;
	HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID *) factory.GetAddressOf());

	if (hr == S_OK) return factory;
	else return nullptr;
}

ComPtr<ID2D1Factory> createD2DFactory()
{
	ComPtr<ID2D1Factory> factory;
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, factory.GetAddressOf());

	if (hr == S_OK) return factory;
	else return nullptr;
}

HRESULT SaveWICBitmapToFile(ComPtr<IWICImagingFactory> factory, ComPtr<IWICBitmap> bitmap, const std::wstring &filename)
{
	ComPtr<IWICStream> stream;
	ComPtr<IWICBitmapEncoder> encoder;
	ComPtr<IWICBitmapFrameEncode> frameEncode;
	WICPixelFormatGUID format = GUID_WICPixelFormat32bppPBGRA;

	HRESULT hr = factory.Get()->CreateStream(stream.GetAddressOf());
	if (hr != S_OK) return hr;
	
	hr = stream.Get()->InitializeFromFilename(filename.c_str(), GENERIC_WRITE);
	if (hr != S_OK) return hr;

	hr = factory->CreateEncoder(GUID_ContainerFormatPng, NULL, encoder.GetAddressOf());
	if (hr != S_OK) return hr;

	hr = encoder.Get()->Initialize(stream.Get(), WICBitmapEncoderNoCache);
	if (hr != S_OK) return hr;

	hr = encoder.Get()->CreateNewFrame(frameEncode.GetAddressOf(), NULL);
	if (hr != S_OK) return hr;

	unsigned width, height;
	hr = bitmap.Get()->GetSize(&width, &height);
	if (hr != S_OK) return hr;

	hr = frameEncode.Get()->Initialize(NULL);
	if (hr != S_OK) return hr;

	hr = frameEncode.Get()->SetSize(width, height);
	if (hr != S_OK) return hr;

	hr = frameEncode.Get()->SetPixelFormat(&format);
	if (hr != S_OK) return hr;

	hr = frameEncode.Get()->WriteSource(bitmap.Get(), NULL);
	if (hr != S_OK) return hr;

	hr = frameEncode.Get()->Commit();
	if (hr != S_OK) return hr;

	hr = encoder.Get()->Commit();
	if (hr != S_OK) return hr;

	return hr;
}

int main()
{
	HRESULT hr = S_OK;

	CoInitialize(0);

	ComPtr<ID2D1Factory> d2dFactory = createD2DFactory();
	ComPtr<IWICImagingFactory> wicFactory = createWICImagingFactory();

	ComPtr<IWICBitmap> wicBitmap = nullptr;
	wicFactory.Get()->CreateBitmap(1000, 1000, GUID_WICPixelFormat32bppPBGRA, WICBitmapCacheOnDemand, wicBitmap.GetAddressOf());

	D2D1_RENDER_TARGET_PROPERTIES renderTargetProperties = D2D1::RenderTargetProperties(
		D2D1_RENDER_TARGET_TYPE_SOFTWARE,
		D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED));

	ComPtr<ID2D1RenderTarget> renderTarget = nullptr;
	hr = d2dFactory->CreateWicBitmapRenderTarget(wicBitmap.Get(), renderTargetProperties, renderTarget.GetAddressOf());

	if (hr != S_OK) return EXIT_FAILURE;

	ID2D1SolidColorBrush *brush;
	hr = renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DeepPink), &brush);

	renderTarget->BeginDraw();

	renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
	renderTarget->DrawRectangle(D2D1::RectF(10.5, 10.5, 100.5, 100.5), brush);

	renderTarget->EndDraw();

	SaveWICBitmapToFile(wicFactory, wicBitmap, L"d3dtest.png");

	return EXIT_SUCCESS;
}