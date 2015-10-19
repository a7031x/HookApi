<h1>Hook API Library</h1>

This library provides a type-safe and thread-safe way to inline hook API or functions. The following example shows how to hook a windows API with a hand written API that calls the origin one.

  int WINAPI MyMessageBoxA(
	  _In_opt_ HWND hWnd,
	  _In_opt_ LPCSTR lpText,
	  _In_opt_ LPCSTR lpCaption,
	  _In_ UINT uType)
  {
  	  lpText = "hooked text";
	    return hookapi::call_origin(MessageBoxA)(hWnd, lpText, lpCaption, uType);
  }

  int main()
  {
	    hookapi::hook(MessageBoxA, MyMessageBoxA);
    	MessageBoxA(nullptr, "text", "caption", MB_OK);
      return 0;
  }

The hookapi::hook verifies the shell API has the same signature as the hooked API, if not the same, a compile time error will exert. There is another type-unsafe method which allows users to hook a code address.

    hookapi::hook_unsafe((PVOID)0x1000E7F0, MyFunction);

There are two ways to call the original API. First of call, if you call the MessageBoxA inside MyMessageBoxA, it leads to a permenant recursion and eventually crashs. If the API has exported symbol, call_origin method is preferred.

    hookapi::call_origin(MessageBoxA)(hWnd, lpText, lpCaption, uType);
    
or assume that you don't know the origin API, it is hooked by address, then use call_origin_by_hook.

    hookapi::call_origin_by_hook(MyMessageBoxA)(hWnd, lpText, lpCaption, uType);

To unhook the API, call

    hookapi::unhook(MessageBoxA);
    

