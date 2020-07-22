// 123.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#include <windows.h>

//000  指向SEH链指针
//004  线程堆栈顶部
//008  线程堆栈底部
//00C  SubSystemTib
//010  FiberData
//014  ArbitraryUserPointer
//018  FS段寄存器在内存中的镜像地址
//020  进程PID
//024  线程ID
//02C  指向线程局部存储指针
//030  PEB结构地址（进程结构）
//034  上个错误号



typedef struct _PEB { // Size: 0x1D8
	/*000*/ UCHAR InheritedAddressSpace;
	/*001*/ UCHAR ReadImageFileExecOptions;
	/*002*/ UCHAR BeingDebugged;
	/*003*/ UCHAR SpareBool; // Allocation size
	/*004*/ HANDLE Mutant;
	/*008*/ HINSTANCE ImageBaseAddress; // Instance
	/*00C*/ VOID *DllList;
	/*010*/ PVOID *ProcessParameters; //PPROCESS_PARAMETERS *ProcessParameters;
	/*014*/ ULONG SubSystemData;
	/*018*/ HANDLE DefaultHeap;
	/*01C*/ KSPIN_LOCK FastPebLock;
	/*020*/ ULONG FastPebLockRoutine;
	/*024*/ ULONG FastPebUnlockRoutine;
	/*028*/ ULONG EnvironmentUpdateCount;
	/*02C*/ ULONG KernelCallbackTable;
	/*030*/ LARGE_INTEGER SystemReserved;
	/*038*/ ULONG FreeList;
	/*03C*/ ULONG TlsExpansionCounter;
	/*040*/ ULONG TlsBitmap;
	/*044*/ LARGE_INTEGER TlsBitmapBits;
	/*04C*/ ULONG ReadOnlySharedMemoryBase;
	/*050*/ ULONG ReadOnlySharedMemoryHeap;
	/*054*/ ULONG ReadOnlyStaticServerData;
	/*058*/ ULONG AnsiCodePageData;
	/*05C*/ ULONG OemCodePageData;
	/*060*/ ULONG UnicodeCaseTableData;
	/*064*/ ULONG NumberOfProcessors;
	/*068*/ LARGE_INTEGER NtGlobalFlag; // Address of a local copy
	/*070*/ LARGE_INTEGER CriticalSectionTimeout;
	/*078*/ ULONG HeapSegmentReserve;
	/*07C*/ ULONG HeapSegmentCommit;
	/*080*/ ULONG HeapDeCommitTotalFreeThreshold;
	/*084*/ ULONG HeapDeCommitFreeBlockThreshold;
	/*088*/ ULONG NumberOfHeaps;
	/*08C*/ ULONG MaximumNumberOfHeaps;
	/*090*/ ULONG ProcessHeaps;
	/*094*/ ULONG GdiSharedHandleTable;
	/*098*/ ULONG ProcessStarterHelper;
	/*09C*/ ULONG GdiDCAttributeList;
	/*0A0*/ KSPIN_LOCK LoaderLock;
	/*0A4*/ ULONG OSMajorVersion;
	/*0A8*/ ULONG OSMinorVersion;
	/*0AC*/ USHORT OSBuildNumber;
	/*0AE*/ USHORT OSCSDVersion;
	/*0B0*/ ULONG OSPlatformId;
	/*0B4*/ ULONG ImageSubsystem;
	/*0B8*/ ULONG ImageSubsystemMajorVersion;
	/*0BC*/ ULONG ImageSubsystemMinorVersion;
	/*0C0*/ ULONG ImageProcessAffinityMask;
	/*0C4*/ ULONG GdiHandleBuffer[0x22];
	/*14C*/ ULONG PostProcessInitRoutine;
	/*150*/ ULONG TlsExpansionBitmap;
	/*154*/ UCHAR TlsExpansionBitmapBits[0x80];
	/*1D4*/ ULONG SessionId;
} PEB, *PPEB;

int main()
{
	//int pid = 0;
	//PPEB pPeb = 0;
	//_asm
	//{
	//	mov eax, dword ptr fs:[20h]
	//	mov pid, eax
	//	mov eax, dword ptr fs : [30h]
	//	mov pPeb, eax
	//}

	/*void *PEB = NULL,
		*Ldr = NULL,
		*Flink = NULL,
		*p = NULL,
		*BaseAddress = NULL,
		*FullDllName = NULL;

	__asm
	{
		mov eax, fs:[0x30]
		mov PEB, eax
	}
	Ldr = *((void **)((unsigned char *)PEB + 0x0c));
	Flink = *((void **)((unsigned char *)Ldr + 0x14));
	p = Flink;
	do
	{
		BaseAddress = *((void **)((unsigned char *)p + 0x10));
		FullDllName = *((void **)((unsigned char *)p + 0x20));
		wprintf(L"FullDllName is %s/n", FullDllName);
		printf("BaseAddress is %x/n", BaseAddress);
		p = *((void **)p);
	} while (Flink != p);*/

	void *PEB = NULL,
		*Ldr = NULL,
		*Flink = NULL,
		*p = NULL,
		*BaseAddress = NULL,
		*FullDllName = NULL;

	__asm
	{
		mov eax, fs:[0x30]
		mov PEB, eax
	}
	Ldr = *((void **)((unsigned char *)PEB + 0x0c));
	Flink = *((void **)((unsigned char *)Ldr + 0x0c));
	p = Flink;
	do
	{
		BaseAddress = *((void **)((unsigned char *)p + 0x18));
		FullDllName = *((void **)((unsigned char *)p + 0x28));
		wprintf(L"FullDllName is %s/n", FullDllName);
		printf("BaseAddress is %x/n", BaseAddress);
		p = *((void **)p);
	} while (Flink != p);
}
