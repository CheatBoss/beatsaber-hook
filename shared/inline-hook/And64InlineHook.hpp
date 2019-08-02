/*
 *  @date   : 2018/04/18
 *  @author : Rprop (r_prop@outlook.com)
 *  https://github.com/Rprop/And64InlineHook
 */
/*
 MIT License

 Copyright (c) 2018 Rprop (r_prop@outlook.com)

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#pragma once
#define A64_MAX_BACKUPS 256
#ifdef __aarch64__
#ifdef __cplusplus
extern "C" {
#endif
enum ele7en_status {
	ELE7EN_ERROR_UNKNOWN = -1,
	ELE7EN_OK = 0,
	ELE7EN_ERROR_NOT_INITIALIZED,
	ELE7EN_ERROR_NOT_EXECUTABLE,
	ELE7EN_ERROR_NOT_REGISTERED,
	ELE7EN_ERROR_NOT_HOOKED,
	ELE7EN_ERROR_ALREADY_REGISTERED,
	ELE7EN_ERROR_ALREADY_HOOKED,
	ELE7EN_ERROR_SO_NOT_FOUND,
	ELE7EN_ERROR_FUNCTION_NOT_FOUND
};


    void A64HookFunction(void *const symbol, void *const replace, void **result);
    void *A64HookFunctionV(void *const symbol, void *const replace,
                           void *const rwx, const uintptr_t rwx_size);
enum ele7en_status registerInlineHook(uint32_t target_addr, uint32_t new_addr, uint32_t **proto_addr);
enum ele7en_status inlineUnHook(uint32_t target_addr);
#ifdef __cplusplus
}
#endif
#endif