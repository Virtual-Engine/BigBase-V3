#pragma once
#include <intrin.h>
#include "fwddec.hpp"
#define DEFINE_RAGE_RTTI(className)    private:\
								virtual void* _0x00() = 0;\
								virtual void* _0x08() = 0;\
								virtual uint32_t _0x10() = 0;\
								virtual className* _0x18(void*) = 0;\
								virtual bool _0x20(void*) = 0;\
								virtual bool _0x28(void**) = 0;\
								virtual void destructor() = 0;\
								public:

namespace rage
{
	class sysMemAllocator
	{
	public:
		DEFINE_RAGE_RTTI(rage::sysMemAllocator);
		virtual void SetQuitOnFail(bool) = 0;
		virtual void* Allocate(std::size_t size, std::size_t align, int subAllocator) = 0;
		virtual void* TryAllocate(std::size_t size, std::size_t align, int subAllocator) = 0;
		virtual void Free(void* pointer) = 0;
		virtual void TryFree(void* pointer) = 0;
		virtual void Resize(void* pointer, std::size_t size) = 0;
		virtual sysMemAllocator* GetAllocator(int allocator) const = 0;
		virtual sysMemAllocator* GetAllocator(int allocator) = 0;
		virtual sysMemAllocator* GetPointerOwner(void* pointer) = 0;
		virtual std::size_t GetSize(void* pointer) const = 0;
		virtual std::size_t GetMemoryUsed(int memoryBucket) = 0;
		virtual std::size_t GetMemoryAvailable() = 0;

	};
#pragma pack(push, 1)
	class tlsContext
	{
	public:
		char gap0[0xB4];                // 0x00 - 0xB4 (180 bytes)
		uint8_t m_unk_byte;             // 0xB4 - 0xB5 (1 byte)
		char gapB5[3];                  // 0xB5 - 0xB8 (3 bytes)
		sysMemAllocator* m_allocator;   // 0xB8 - 0xC0 (8 bytes)
		char gapC0[0x798];              // 0xC0 - 0x858 (1944 bytes)
		scrThread* m_script_thread;     // 0x858 - 0x860 (8 bytes)
		bool m_is_script_thread_active; // 0x860 - 0x861 (1 byte)

		static tlsContext* get()
		{
			return *reinterpret_cast<tlsContext**>(__readgsqword(0x58));
		}
	};
#pragma pack(pop)

	static_assert(sizeof(tlsContext) == 0x861, "tlsContext size is incorrect");
}