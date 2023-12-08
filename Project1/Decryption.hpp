#pragma once
#include"Driver.h"
#include"includes.hpp"
#include"structures.hpp"
QWORD get_refdef()
{
    uint32_t crypt_0 = read<uint32_t>(oBaseAddress + refdef_ptr);
    uint32_t crypt_1 = read<uint32_t>(oBaseAddress + refdef_ptr + 0x4);
    uint32_t crypt_2 = read<uint32_t>(oBaseAddress + refdef_ptr + 0x8);

    // lower 32 bits
    uint32_t entry_1 = (uint32_t)(oBaseAddress + refdef_ptr);
    uint32_t entry_2 = (uint32_t)(oBaseAddress + refdef_ptr + 0x4);

    // decryption
    uint32_t _low = entry_1 ^ crypt_2;
    uint32_t _high = entry_2 ^ crypt_2;
    uint32_t low_bit = crypt_0 ^ _low * (_low + 2);
    uint32_t high_bit = crypt_1 ^ _high * (_high + 2);
    auto ret = ((QWORD)high_bit << 32) + low_bit;
    if (ret)
        return ret;
    else
        return 0;
}

uintptr_t decrypt_client_info()
{
    //auto Peb = __readgsqword(0x60);
    auto Peb = Pebadd;//driver function
    uint64_t mb = oBaseAddress;
    uint64_t rax = mb, rbx = mb, rcx = mb, rdx = mb, rdi = mb, rsi = mb, r8 = mb, r9 = mb, r10 = mb, r11 = mb, r12 = mb, r13 = mb, r14 = mb, r15 = mb;

    rbx = read<uintptr_t>(oBaseAddress + 0x11DB8098);
    if (!rbx)
        return rbx;

    rcx = Peb;              //mov rcx, gs:[rax]
    rbx -= rcx;             //sub rbx, rcx
    rax = 0;                //and rax, 0xFFFFFFFFC0000000
    rdx = 0x693186CC4D1F9DB;                //mov rdx, 0x693186CC4D1F9DB
    rbx *= rdx;             //imul rbx, rdx
    rax = _rotl64(rax, 0x10);               //rol rax, 0x10
    rdx = 0x57548B4D82F080EE;               //mov rdx, 0x57548B4D82F080EE
    rax ^= read<uintptr_t>(oBaseAddress + 0x95040E6);             //xor rax, [0x000000000736E6ED]
    rbx += rdx;             //add rbx, rdx
    rax = _byteswap_uint64(rax);            //bswap rax
    rbx *= read<uintptr_t>(rax + 0x13);             //imul rbx, [rax+0x13]
    rax = rbx;              //mov rax, rbx
    rbx >>= 0x20;           //shr rbx, 0x20
    rbx ^= rax;             //xor rbx, rax
    rbx += rcx;             //add rbx, rcx
    return rbx;
};
uintptr_t decrypt_client_base(uintptr_t client_info)
{
    auto Peb = Pebadd;//driver function
    const uint64_t mb = oBaseAddress;
    uint64_t rax = mb, rbx = mb, rcx = mb, rdx = mb, rdi = mb, rsi = mb, r8 = mb, r9 = mb, r10 = mb, r11 = mb, r12 = mb, r13 = mb, r14 = mb, r15 = mb;
    rax = read<uintptr_t>(client_info + 0x182948);
    if (!rax)
        return rax;
    r11 = ~Peb;              //mov r11, gs:[rcx]
    rcx = r11;              //mov rcx, r11
    //failed to translate: mov [rsp+0x3D0], r13
    rcx = _rotl64(rcx, 0x21);               //rol rcx, 0x21
    rcx &= 0xF;
    switch (rcx) {
    case 0:
    {
        r9 = read<uintptr_t>(oBaseAddress + 0x950410E);               //mov r9, [0x0000000006745F31]
        rbx = oBaseAddress;           //lea rbx, [0xFFFFFFFFFD241E10]
        rcx = 0x9141C45BFD5B39F7;               //mov rcx, 0x9141C45BFD5B39F7
        rax ^= rcx;             //xor rax, rcx
        rcx = rax + rbx * 1;            //lea rcx, [rax+rbx*1]
        rax = 0xF605A67470E7C53D;               //mov rax, 0xF605A67470E7C53D
        rcx *= rax;             //imul rcx, rax
        rax = r11;              //mov rax, r11
        uintptr_t RSP_0x50;
        RSP_0x50 = oBaseAddress + 0x6E33AF72;                 //lea rcx, [0x000000006B57CD8E] : RSP+0x50
        rax ^= RSP_0x50;                //xor rax, [rsp+0x50]
        rcx -= rax;             //sub rcx, rax
        rax = r11 + 0xffffffffd10685d8;                 //lea rax, [r11-0x2EF97A28]
        rcx -= rbx;             //sub rcx, rbx
        rax += rcx;             //add rax, rcx
        rcx = oBaseAddress + 0x526CB4F4;              //lea rcx, [0x000000004F90D237]
        rcx = ~rcx;             //not rcx
        rcx -= r11;             //sub rcx, r11
        rax += rcx;             //add rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x1A;           //shr rcx, 0x1A
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x34;           //shr rcx, 0x34
        rax ^= rcx;             //xor rax, rcx
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r9;              //xor rcx, r9
        rcx = ~rcx;             //not rcx
        rax *= read<uintptr_t>(rcx + 0x19);             //imul rax, [rcx+0x19]
        return rax;
    }
    case 1:
    {
        r10 = read<uintptr_t>(oBaseAddress + 0x950410E);              //mov r10, [0x0000000006745A98]
        rbx = oBaseAddress;           //lea rbx, [0xFFFFFFFFFD241983]
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x24;           //shr rcx, 0x24
        rax ^= rcx;             //xor rax, rcx
        rcx = 0xE570A6F93EC9464F;               //mov rcx, 0xE570A6F93EC9464F
        rax *= rcx;             //imul rax, rcx
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r10;             //xor rcx, r10
        rcx = ~rcx;             //not rcx
        rax *= read<uintptr_t>(rcx + 0x19);             //imul rax, [rcx+0x19]
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x24;           //shr rcx, 0x24
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x11;           //shr rcx, 0x11
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x22;           //shr rcx, 0x22
        rax ^= rcx;             //xor rax, rcx
        rax -= rbx;             //sub rax, rbx
        rax += r11;             //add rax, r11
        rcx = 0x14F095F380F9EB43;               //mov rcx, 0x14F095F380F9EB43
        rax += rcx;             //add rax, rcx
        return rax;
    }
    case 2:
    {
        r10 = read<uintptr_t>(oBaseAddress + 0x950410E);              //mov r10, [0x00000000067455E7]
        rcx = 0x8ADB88DACDCF2087;               //mov rcx, 0x8ADB88DACDCF2087
        rax *= rcx;             //imul rax, rcx
        rcx = 0x7962CBE13BD24CEA;               //mov rcx, 0x7962CBE13BD24CEA
        rax += rcx;             //add rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x10;           //shr rcx, 0x10
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x20;           //shr rcx, 0x20
        rax ^= rcx;             //xor rax, rcx
        rax += r11;             //add rax, r11
        rax += r11;             //add rax, r11
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r10;             //xor rcx, r10
        rcx = ~rcx;             //not rcx
        rax *= read<uintptr_t>(rcx + 0x19);             //imul rax, [rcx+0x19]
        rax -= r11;             //sub rax, r11
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x1D;           //shr rcx, 0x1D
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x3A;           //shr rcx, 0x3A
        rax ^= rcx;             //xor rax, rcx
        return rax;
    }
    case 3:
    {
        r10 = read<uintptr_t>(oBaseAddress + 0x950410E);              //mov r10, [0x0000000006745207]
        rbx = oBaseAddress;           //lea rbx, [0xFFFFFFFFFD2410F2]
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x25;           //shr rcx, 0x25
        rcx ^= rax;             //xor rcx, rax
        rax = 0x99B04B837FD2242B;               //mov rax, 0x99B04B837FD2242B
        rax += rcx;             //add rax, rcx
        rax += rbx;             //add rax, rbx
        rax ^= r11;             //xor rax, r11
        rax -= rbx;             //sub rax, rbx
        rcx = oBaseAddress + 0x11751E8B;              //lea rcx, [0x000000000E992BE9]
        rcx = ~rcx;             //not rcx
        rcx -= r11;             //sub rcx, r11
        rax += rcx;             //add rax, rcx
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r10;             //xor rcx, r10
        rcx = ~rcx;             //not rcx
        rax *= read<uintptr_t>(rcx + 0x19);             //imul rax, [rcx+0x19]
        rcx = 0xDA47FAB853EFDBF7;               //mov rcx, 0xDA47FAB853EFDBF7
        rax *= rcx;             //imul rax, rcx
        return rax;
    }
    case 4:
    {
        r10 = read<uintptr_t>(oBaseAddress + 0x950410E);              //mov r10, [0x0000000006744D4C]
        rbx = oBaseAddress;           //lea rbx, [0xFFFFFFFFFD240C2B]
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x2;            //shr rcx, 0x02
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x4;            //shr rcx, 0x04
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x8;            //shr rcx, 0x08
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x10;           //shr rcx, 0x10
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x20;           //shr rcx, 0x20
        rax ^= rcx;             //xor rax, rcx
        rcx = 0x718CFE6D52D76081;               //mov rcx, 0x718CFE6D52D76081
        rax *= rcx;             //imul rax, rcx
        rcx = r11;              //mov rcx, r11
        rcx ^= rax;             //xor rcx, rax
        rdx = 0;                //and rdx, 0xFFFFFFFFC0000000
        rax = oBaseAddress + 0x746D9936;              //lea rax, [0x000000007191A2E7]
        rcx ^= rax;             //xor rcx, rax
        rdx = _rotl64(rdx, 0x10);               //rol rdx, 0x10
        rdx ^= r10;             //xor rdx, r10
        rax = 0x6A0BA8494B6820F5;               //mov rax, 0x6A0BA8494B6820F5
        rdx = ~rdx;             //not rdx
        rcx *= read<uintptr_t>(rdx + 0x19);             //imul rcx, [rdx+0x19]
        rax += rcx;             //add rax, rcx
        rax ^= rbx;             //xor rax, rbx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x15;           //shr rcx, 0x15
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x2A;           //shr rcx, 0x2A
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x1C;           //shr rcx, 0x1C
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x38;           //shr rcx, 0x38
        rax ^= rcx;             //xor rax, rcx
        return rax;
    }
    case 5:
    {
        r9 = read<uintptr_t>(oBaseAddress + 0x950410E);               //mov r9, [0x00000000067447D2]
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x15;           //shr rcx, 0x15
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x2A;           //shr rcx, 0x2A
        rax ^= rcx;             //xor rax, rcx
        rcx = 0x6B4D10E3FCFC0235;               //mov rcx, 0x6B4D10E3FCFC0235
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x3;            //shr rcx, 0x03
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x6;            //shr rcx, 0x06
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0xC;            //shr rcx, 0x0C
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x18;           //shr rcx, 0x18
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x30;           //shr rcx, 0x30
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x1A;           //shr rcx, 0x1A
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x34;           //shr rcx, 0x34
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x1C;           //shr rcx, 0x1C
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x38;           //shr rcx, 0x38
        rax ^= rcx;             //xor rax, rcx
        uintptr_t RSP_0x70;
        RSP_0x70 = 0x9FE7D7D2C91086EF;          //mov rcx, 0x9FE7D7D2C91086EF : RSP+0x70
        rax *= RSP_0x70;                //imul rax, [rsp+0x70]
        uintptr_t RSP_0x48;
        RSP_0x48 = 0x3B044E06AA0DC65D;          //mov rcx, 0x3B044E06AA0DC65D : RSP+0x48
        rax += RSP_0x48;                //add rax, [rsp+0x48]
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r9;              //xor rcx, r9
        rcx = ~rcx;             //not rcx
        rax *= read<uintptr_t>(rcx + 0x19);             //imul rax, [rcx+0x19]
        return rax;
    }
    case 6:
    {
        r9 = read<uintptr_t>(oBaseAddress + 0x950410E);               //mov r9, [0x000000000674426D]
        rbx = oBaseAddress;           //lea rbx, [0xFFFFFFFFFD240158]
        rcx = rax;              //mov rcx, rax
        rcx >>= 0xF;            //shr rcx, 0x0F
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x1E;           //shr rcx, 0x1E
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x3C;           //shr rcx, 0x3C
        rax ^= rcx;             //xor rax, rcx
        rax -= r11;             //sub rax, r11
        rax ^= r11;             //xor rax, r11
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r9;              //xor rcx, r9
        rcx = ~rcx;             //not rcx
        rcx = read<uintptr_t>(rcx + 0x19);              //mov rcx, [rcx+0x19]
        uintptr_t RSP_0x40;
        RSP_0x40 = 0xB64C05FA8BB41ED5;          //mov rcx, 0xB64C05FA8BB41ED5 : RSP+0x40
        rcx *= RSP_0x40;                //imul rcx, [rsp+0x40]
        rax *= rcx;             //imul rax, rcx
        rax -= rbx;             //sub rax, rbx
        rcx = 0xA1839DE961442277;               //mov rcx, 0xA1839DE961442277
        rax *= rcx;             //imul rax, rcx
        return rax;
    }
    case 7:
    {
        r10 = read<uintptr_t>(oBaseAddress + 0x950410E);              //mov r10, [0x0000000006743DE5]
        rcx = oBaseAddress + 0x7E9B;          //lea rcx, [0xFFFFFFFFFD247767]
        rdx = r11;              //mov rdx, r11
        rax += rcx;             //add rax, rcx
        rdx = ~rdx;             //not rdx
        rax += rdx;             //add rax, rdx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0xD;            //shr rcx, 0x0D
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x1A;           //shr rcx, 0x1A
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x34;           //shr rcx, 0x34
        rax ^= rcx;             //xor rax, rcx
        rcx = r11;              //mov rcx, r11
        uintptr_t RSP_0x50;
        RSP_0x50 = oBaseAddress + 0x2B12;             //lea rcx, [0xFFFFFFFFFD2427E2] : RSP+0x50
        rcx ^= RSP_0x50;                //xor rcx, [rsp+0x50]
        rax -= rcx;             //sub rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x27;           //shr rcx, 0x27
        rax ^= rcx;             //xor rax, rcx
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r10;             //xor rcx, r10
        rcx = ~rcx;             //not rcx
        rax *= read<uintptr_t>(rcx + 0x19);             //imul rax, [rcx+0x19]
        rcx = 0x6B0468CD6B4B36F5;               //mov rcx, 0x6B0468CD6B4B36F5
        rax *= rcx;             //imul rax, rcx
        rcx = 0x67D32343BA582459;               //mov rcx, 0x67D32343BA582459
        rax -= rcx;             //sub rax, rcx
        rcx = 0x2AB381DC49040AEF;               //mov rcx, 0x2AB381DC49040AEF
        rax ^= rcx;             //xor rax, rcx
        return rax;
    }
    case 8:
    {
        r10 = read<uintptr_t>(oBaseAddress + 0x950410E);              //mov r10, [0x00000000067438E7]
        rbx = oBaseAddress;           //lea rbx, [0xFFFFFFFFFD23F7D2]
        rcx = 0xF27764D7BCC134E1;               //mov rcx, 0xF27764D7BCC134E1
        rax *= rcx;             //imul rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x7;            //shr rcx, 0x07
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0xE;            //shr rcx, 0x0E
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x1C;           //shr rcx, 0x1C
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x38;           //shr rcx, 0x38
        rax ^= rcx;             //xor rax, rcx
        rax ^= rbx;             //xor rax, rbx
        rcx = 0xC3107C6F6CB6AAB7;               //mov rcx, 0xC3107C6F6CB6AAB7
        rax *= rcx;             //imul rax, rcx
        rcx = 0xD1B5E7C8461A7E03;               //mov rcx, 0xD1B5E7C8461A7E03
        rax ^= rcx;             //xor rax, rcx
        rcx = oBaseAddress + 0x4977696C;              //lea rcx, [0x00000000469B5F71]
        rcx = ~rcx;             //not rcx
        rcx += r11;             //add rcx, r11
        rax += rcx;             //add rax, rcx
        rax += 0xFFFFFFFFFFFF4E09;              //add rax, 0xFFFFFFFFFFFF4E09
        rcx = r11;              //mov rcx, r11
        rcx -= rbx;             //sub rcx, rbx
        rax += rcx;             //add rax, rcx
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r10;             //xor rcx, r10
        rcx = ~rcx;             //not rcx
        rax *= read<uintptr_t>(rcx + 0x19);             //imul rax, [rcx+0x19]
        return rax;
    }
    case 9:
    {
        r10 = read<uintptr_t>(oBaseAddress + 0x950410E);              //mov r10, [0x0000000006743443]
        rbx = oBaseAddress;           //lea rbx, [0xFFFFFFFFFD23F32E]
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x23;           //shr rcx, 0x23
        rax ^= rcx;             //xor rax, rcx
        rcx = 0xA7B0F0AA378850A7;               //mov rcx, 0xA7B0F0AA378850A7
        rax *= rcx;             //imul rax, rcx
        rax ^= rbx;             //xor rax, rbx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x1B;           //shr rcx, 0x1B
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x36;           //shr rcx, 0x36
        rax ^= rcx;             //xor rax, rcx
        rcx = rbx + 0xd85;              //lea rcx, [rbx+0xD85]
        rcx += r11;             //add rcx, r11
        rax += rcx;             //add rax, rcx
        rax -= rbx;             //sub rax, rbx
        uintptr_t RSP_0x60;
        RSP_0x60 = 0x4E5E1AE762C3863A;          //mov rcx, 0x4E5E1AE762C3863A : RSP+0x60
        rax ^= RSP_0x60;                //xor rax, [rsp+0x60]
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r10;             //xor rcx, r10
        rcx = ~rcx;             //not rcx
        rax *= read<uintptr_t>(rcx + 0x19);             //imul rax, [rcx+0x19]
        return rax;
    }
    case 10:
    {
        r9 = read<uintptr_t>(oBaseAddress + 0x950410E);               //mov r9, [0x0000000006742F80]
        rbx = oBaseAddress;           //lea rbx, [0xFFFFFFFFFD23EE6B]
        r13 = oBaseAddress + 0xF084;          //lea r13, [0xFFFFFFFFFD24DED7]
        rcx = 0x98CD10A39FEEABC3;               //mov rcx, 0x98CD10A39FEEABC3
        rax *= rcx;             //imul rax, rcx
        rcx = rbx + 0x8af0;             //lea rcx, [rbx+0x8AF0]
        rcx += r11;             //add rcx, r11
        rax += rcx;             //add rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x10;           //shr rcx, 0x10
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x20;           //shr rcx, 0x20
        rax ^= rcx;             //xor rax, rcx
        rcx = r11;              //mov rcx, r11
        rcx = ~rcx;             //not rcx
        rcx ^= r13;             //xor rcx, r13
        rax += rcx;             //add rax, rcx
        rcx = 0xDF8A1660CBF5F30F;               //mov rcx, 0xDF8A1660CBF5F30F
        rax *= rcx;             //imul rax, rcx
        rcx = 0xA829D63D19635A8D;               //mov rcx, 0xA829D63D19635A8D
        rax ^= rcx;             //xor rax, rcx
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r9;              //xor rcx, r9
        rcx = ~rcx;             //not rcx
        rax *= read<uintptr_t>(rcx + 0x19);             //imul rax, [rcx+0x19]
        rax ^= r11;             //xor rax, r11
        return rax;
    }
    case 11:
    {
        r10 = read<uintptr_t>(oBaseAddress + 0x950410E);              //mov r10, [0x0000000006742AFD]
        rbx = oBaseAddress;           //lea rbx, [0xFFFFFFFFFD23E9E8]
        rdx = rax;              //mov rdx, rax
        rdx >>= 0x23;           //shr rdx, 0x23
        rcx = oBaseAddress + 0x17E7D121;              //lea rcx, [0x00000000150BB7C5]
        rdx ^= rcx;             //xor rdx, rcx
        rcx = r11 + 0x1;                //lea rcx, [r11+0x01]
        rdx ^= r11;             //xor rdx, r11
        rdx ^= rax;             //xor rdx, rax
        rax = oBaseAddress + 0x7D39B186;              //lea rax, [0x000000007A5D9816]
        rax *= rcx;             //imul rax, rcx
        rax += rdx;             //add rax, rdx
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r10;             //xor rcx, r10
        rcx = ~rcx;             //not rcx
        rax *= read<uintptr_t>(rcx + 0x19);             //imul rax, [rcx+0x19]
        rcx = rbx + 0x8cb1;             //lea rcx, [rbx+0x8CB1]
        rcx += r11;             //add rcx, r11
        rax ^= rcx;             //xor rax, rcx
        rax ^= r11;             //xor rax, r11
        rcx = 0x71B5B118240CFD7D;               //mov rcx, 0x71B5B118240CFD7D
        rax *= rcx;             //imul rax, rcx
        rcx = rbx + 0x2611654c;                 //lea rcx, [rbx+0x2611654C]
        rcx += r11;             //add rcx, r11
        rax += rcx;             //add rax, rcx
        return rax;
    }
    case 12:
    {
        r10 = read<uintptr_t>(oBaseAddress + 0x950410E);              //mov r10, [0x0000000006742716]
        rbx = oBaseAddress;           //lea rbx, [0xFFFFFFFFFD23E601]
        rdx = oBaseAddress + 0x4291859E;              //lea rdx, [0x000000003FB56B45]
        rax -= rbx;             //sub rax, rbx
        rcx = rdx;              //mov rcx, rdx
        rcx = ~rcx;             //not rcx
        rcx ^= r11;             //xor rcx, r11
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x10;           //shr rcx, 0x10
        rax ^= rcx;             //xor rax, rcx
        rdx = 0;                //and rdx, 0xFFFFFFFFC0000000
        rdx = _rotl64(rdx, 0x10);               //rol rdx, 0x10
        rdx ^= r10;             //xor rdx, r10
        rcx = rax;              //mov rcx, rax
        rdx = ~rdx;             //not rdx
        rcx >>= 0x20;           //shr rcx, 0x20
        rax ^= rcx;             //xor rax, rcx
        rcx = 0x6A01EB295C695943;               //mov rcx, 0x6A01EB295C695943
        rax *= rcx;             //imul rax, rcx
        rcx = 0x9BBE6575DCB15C28;               //mov rcx, 0x9BBE6575DCB15C28
        rax ^= rcx;             //xor rax, rcx
        rax *= read<uintptr_t>(rdx + 0x19);             //imul rax, [rdx+0x19]
        rcx = 0x9A76A1C3B04C8361;               //mov rcx, 0x9A76A1C3B04C8361
        rax *= rcx;             //imul rax, rcx
        rax -= rbx;             //sub rax, rbx
        return rax;
    }
    case 13:
    {
        r10 = read<uintptr_t>(oBaseAddress + 0x950410E);              //mov r10, [0x0000000006742275]
        rbx = oBaseAddress;           //lea rbx, [0xFFFFFFFFFD23E160]
        rax ^= rbx;             //xor rax, rbx
        rcx = 0x424E7D3CE7A4BDA3;               //mov rcx, 0x424E7D3CE7A4BDA3
        rax *= rcx;             //imul rax, rcx
        rcx = oBaseAddress + 0x1A767856;              //lea rcx, [0x00000000179A5582]
        rcx = ~rcx;             //not rcx
        rcx ^= r11;             //xor rcx, r11
        rax += rcx;             //add rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0xF;            //shr rcx, 0x0F
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x1E;           //shr rcx, 0x1E
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x3C;           //shr rcx, 0x3C
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x1;            //shr rcx, 0x01
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x2;            //shr rcx, 0x02
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x4;            //shr rcx, 0x04
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x8;            //shr rcx, 0x08
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x10;           //shr rcx, 0x10
        rax ^= rcx;             //xor rax, rcx
        rdx = 0;                //and rdx, 0xFFFFFFFFC0000000
        rdx = _rotl64(rdx, 0x10);               //rol rdx, 0x10
        rcx = rax;              //mov rcx, rax
        rdx ^= r10;             //xor rdx, r10
        rcx >>= 0x20;           //shr rcx, 0x20
        rdx = ~rdx;             //not rdx
        rax ^= rcx;             //xor rax, rcx
        rax *= read<uintptr_t>(rdx + 0x19);             //imul rax, [rdx+0x19]
        rdx = oBaseAddress + 0x31EB9108;              //lea rdx, [0x000000002F0F7007]
        rdx += r11;             //add rdx, r11
        rcx = rax;              //mov rcx, rax
        rax = 0x8DB30096C278A251;               //mov rax, 0x8DB30096C278A251
        rcx *= rax;             //imul rcx, rax
        rax = rdx;              //mov rax, rdx
        rax ^= rcx;             //xor rax, rcx
        return rax;
    }
    case 14:
    {
        r10 = read<uintptr_t>(oBaseAddress + 0x950410E);              //mov r10, [0x0000000006741D61]
        rbx = oBaseAddress;           //lea rbx, [0xFFFFFFFFFD23DC41]
        rdx = oBaseAddress + 0xA832;          //lea rdx, [0xFFFFFFFFFD24809E]
        rdx += r11;             //add rdx, r11
        rdx ^= rax;             //xor rdx, rax
        rax = r11;              //mov rax, r11
        rax = ~rax;             //not rax
        rax += rdx;             //add rax, rdx
        rax -= rbx;             //sub rax, rbx
        rax -= 0x2FECE2F9;              //sub rax, 0x2FECE2F9
        rcx = oBaseAddress + 0x4948;          //lea rcx, [0xFFFFFFFFFD2421DD]
        rcx += r11;             //add rcx, r11
        rax += rcx;             //add rax, rcx
        rcx = 0xE986304E17E64F7D;               //mov rcx, 0xE986304E17E64F7D
        rax *= rcx;             //imul rax, rcx
        rcx = oBaseAddress + 0x5BB7;          //lea rcx, [0xFFFFFFFFFD243667]
        rcx = ~rcx;             //not rcx
        rcx -= r11;             //sub rcx, r11
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x1A;           //shr rcx, 0x1A
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x34;           //shr rcx, 0x34
        rax ^= rcx;             //xor rax, rcx
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r10;             //xor rcx, r10
        rcx = ~rcx;             //not rcx
        rax *= read<uintptr_t>(rcx + 0x19);             //imul rax, [rcx+0x19]
        rcx = r11;              //mov rcx, r11
        rcx = ~rcx;             //not rcx
        uintptr_t RSP_0xFFFFFFFFFFFFFF88;
        RSP_0xFFFFFFFFFFFFFF88 = oBaseAddress + 0x30A5920C;           //lea rcx, [0x000000002DC96E58] : RBP+0xFFFFFFFFFFFFFF88
        rcx ^= RSP_0xFFFFFFFFFFFFFF88;          //xor rcx, [rbp-0x78]
        rax += rcx;             //add rax, rcx
        return rax;
    }
    case 15:
    {
        r10 = read<uintptr_t>(oBaseAddress + 0x950410E);              //mov r10, [0x0000000006741812]
        rbx = oBaseAddress;           //lea rbx, [0xFFFFFFFFFD23D6FD]
        rdx = oBaseAddress + 0x56C36699;              //lea rdx, [0x0000000053E73CED]
        rcx = 0x14288A7031FA1D2A;               //mov rcx, 0x14288A7031FA1D2A
        rax += rcx;             //add rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0xA;            //shr rcx, 0x0A
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x14;           //shr rcx, 0x14
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x28;           //shr rcx, 0x28
        rax ^= rcx;             //xor rax, rcx
        rcx = 0xF471F0FE111CB275;               //mov rcx, 0xF471F0FE111CB275
        rax *= rcx;             //imul rax, rcx
        rcx = rdx;              //mov rcx, rdx
        rcx = ~rcx;             //not rcx
        rcx *= r11;             //imul rcx, r11
        rax ^= rcx;             //xor rax, rcx
        rax -= r11;             //sub rax, r11
        rax -= rbx;             //sub rax, rbx
        rax -= 0x57EC1422;              //sub rax, 0x57EC1422
        rcx = oBaseAddress + 0xF4C;           //lea rcx, [0xFFFFFFFFFD23E392]
        rcx *= r11;             //imul rcx, r11
        rax += rcx;             //add rax, rcx
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r10;             //xor rcx, r10
        rcx = ~rcx;             //not rcx
        rax *= read<uintptr_t>(rcx + 0x19);             //imul rax, [rcx+0x19]
        rcx = oBaseAddress + 0x1793;          //lea rcx, [0xFFFFFFFFFD23EB47]
        rcx -= r11;             //sub rcx, r11
        rax ^= rcx;             //xor rax, rcx
        return rax;
    }
    }
}
uintptr_t decrypt_bone_base()
{
    auto Peb = Pebadd;
    const uint64_t mb = oBaseAddress;
    uint64_t rax = mb, rbx = mb, rcx = mb, rdx = mb, rdi = mb, rsi = mb, r8 = mb, r9 = mb, r10 = mb, r11 = mb, r12 = mb, r13 = mb, r14 = mb, r15 = mb;
    rdx = read<uintptr_t>(oBaseAddress + 0xCF98018);
    if (!rdx)
        return rdx;
    r11 = Peb;              //mov r11, gs:[rax]
    rax = r11;              //mov rax, r11
    rax = _rotr64(rax, 0x15);               //ror rax, 0x15
    rax &= 0xF;
    switch (rax) {
    case 0:
    {
        r9 = Pebadd;               //mov r9, [0x00000000070C1F2B]
        r15 = oBaseAddress + 0x629DAB46;              //lea r15, [0x000000006059886E]
        r13 = oBaseAddress + 0x9895;          //lea r13, [0xFFFFFFFFFDBC75B1]
        rax = 0xAC145E023332D189;               //mov rax, 0xAC145E023332D189
        rdx ^= rax;             //xor rdx, rax
        rax = r15;              //mov rax, r15
        rax = ~rax;             //not rax
        rax *= r11;             //imul rax, r11
        rdx += rax;             //add rdx, rax
        rax = 0xFDEBD2F07B05670D;               //mov rax, 0xFDEBD2F07B05670D
        rdx *= rax;             //imul rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x3;            //shr rax, 0x03
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x6;            //shr rax, 0x06
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0xC;            //shr rax, 0x0C
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x18;           //shr rax, 0x18
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x30;           //shr rax, 0x30
        rdx ^= rax;             //xor rdx, rax
        rax = 0xF0805972B46E082;                //mov rax, 0xF0805972B46E082
        rdx -= rax;             //sub rdx, rax
        rax = r11;              //mov rax, r11
        rax ^= r13;             //xor rax, r13
        rdx += rax;             //add rdx, rax
        rax = 0;                //and rax, 0xFFFFFFFFC0000000
        rax = _rotl64(rax, 0x10);               //rol rax, 0x10
        rax ^= r9;              //xor rax, r9
        rax = _byteswap_uint64(rax);            //bswap rax
        rdx *= read<uintptr_t>(rax + 0x11);             //imul rdx, [rax+0x11]
        rax = rdx;              //mov rax, rdx
        rax >>= 0x4;            //shr rax, 0x04
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x8;            //shr rax, 0x08
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x10;           //shr rax, 0x10
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x20;           //shr rax, 0x20
        rdx ^= rax;             //xor rdx, rax
        return rdx;
    }
    case 1:
    {
        r9 = read<uintptr_t>(oBaseAddress + 0x95041FC);               //mov r9, [0x00000000070C18AD]
        rax = 0;                //and rax, 0xFFFFFFFFC0000000
        rax = _rotl64(rax, 0x10);               //rol rax, 0x10
        rax ^= r9;              //xor rax, r9
        rax = _byteswap_uint64(rax);            //bswap rax
        rdx *= read<uintptr_t>(rax + 0x11);             //imul rdx, [rax+0x11]
        rax = 0x3ECBF33498144A56;               //mov rax, 0x3ECBF33498144A56
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0xA;            //shr rax, 0x0A
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x14;           //shr rax, 0x14
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x28;           //shr rax, 0x28
        rdx ^= rax;             //xor rdx, rax
        rax = 0x87F19886B363B05B;               //mov rax, 0x87F19886B363B05B
        rdx *= rax;             //imul rdx, rax
        rdx -= r11;             //sub rdx, r11
        rax = 0x6303659E1F345AFF;               //mov rax, 0x6303659E1F345AFF
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x15;           //shr rax, 0x15
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x2A;           //shr rax, 0x2A
        rdx ^= rax;             //xor rdx, rax
        rdx += r11;             //add rdx, r11
        return rdx;
    }
    case 2:
    {
        r10 = read<uintptr_t>(oBaseAddress + 0x95041FC);              //mov r10, [0x00000000070C142D]
        r13 = oBaseAddress + 0x6F7AC17A;              //lea r13, [0x000000006D369398]
        rdx += r11;             //add rdx, r11
        rax = rdx;              //mov rax, rdx
        rax >>= 0x13;           //shr rax, 0x13
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x26;           //shr rax, 0x26
        rdx ^= rax;             //xor rdx, rax
        rax = oBaseAddress + 0x62BA;          //lea rax, [0xFFFFFFFFFDBC31E1]
        rax -= r11;             //sub rax, r11
        rdx += rax;             //add rdx, rax
        rax = 0x6367F6E201B667AF;               //mov rax, 0x6367F6E201B667AF
        rdx *= rax;             //imul rdx, rax
        rax = 0x7EA109C91958478C;               //mov rax, 0x7EA109C91958478C
        rdx -= rax;             //sub rdx, rax
        rdx ^= r11;             //xor rdx, r11
        rdx ^= r13;             //xor rdx, r13
        rax = 0x79658B29969CD86A;               //mov rax, 0x79658B29969CD86A
        rdx -= rax;             //sub rdx, rax
        rax = 0;                //and rax, 0xFFFFFFFFC0000000
        rax = _rotl64(rax, 0x10);               //rol rax, 0x10
        rax ^= r10;             //xor rax, r10
        rax = _byteswap_uint64(rax);            //bswap rax
        rdx *= read<uintptr_t>(rax + 0x11);             //imul rdx, [rax+0x11]
        return rdx;
    }
    case 3:
    {
        r9 = read<uintptr_t>(oBaseAddress + 0x95041FC);               //mov r9, [0x00000000070C0F7D]
        r14 = oBaseAddress + 0xF8CE;          //lea r14, [0xFFFFFFFFFDBCC63C]
        rax = rdx;              //mov rax, rdx
        rax >>= 0x20;           //shr rax, 0x20
        rdx ^= rax;             //xor rdx, rax
        rax = 0xEA0A19EF431520D;                //mov rax, 0xEA0A19EF431520D
        rdx ^= rax;             //xor rdx, rax
        rax = 0xFFFFFFFF93B5ED93;               //mov rax, 0xFFFFFFFF93B5ED93
        rax -= r11;             //sub rax, r11
        rax -= oBaseAddress;          //sub rax, [rsp+0xA0] -- didn't find trace -> use base
        rdx += rax;             //add rdx, rax
        rax = r11;              //mov rax, r11
        rax *= r14;             //imul rax, r14
        rdx -= rax;             //sub rdx, rax
        rax = 0x39F863E9187B3F65;               //mov rax, 0x39F863E9187B3F65
        rdx *= rax;             //imul rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x1F;           //shr rax, 0x1F
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x3E;           //shr rax, 0x3E
        rdx ^= rax;             //xor rdx, rax
        rax = 0x44AFB2020B72DD38;               //mov rax, 0x44AFB2020B72DD38
        rdx += rax;             //add rdx, rax
        rax = 0;                //and rax, 0xFFFFFFFFC0000000
        rax = _rotl64(rax, 0x10);               //rol rax, 0x10
        rax ^= r9;              //xor rax, r9
        rax = _byteswap_uint64(rax);            //bswap rax
        rdx *= read<uintptr_t>(rax + 0x11);             //imul rdx, [rax+0x11]
        return rdx;
    }
    case 4:
    {
        r9 = read<uintptr_t>(oBaseAddress + 0x95041FC);               //mov r9, [0x00000000070C0A62]
        r15 = oBaseAddress + 0xD76E;          //lea r15, [0xFFFFFFFFFDBC9FC1]
        rax = r15;              //mov rax, r15
        rax = ~rax;             //not rax
        rax ^= r11;             //xor rax, r11
        rdx -= rax;             //sub rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x24;           //shr rax, 0x24
        rdx ^= rax;             //xor rdx, rax
        rax = 0x2690031C441C94ED;               //mov rax, 0x2690031C441C94ED
        rdx *= rax;             //imul rdx, rax
        rdx ^= r11;             //xor rdx, r11
        rax = 0xA3A6498F1C56BC17;               //mov rax, 0xA3A6498F1C56BC17
        rdx ^= rax;             //xor rdx, rax
        rdx -= r11;             //sub rdx, r11
        rax = 0;                //and rax, 0xFFFFFFFFC0000000
        rax = _rotl64(rax, 0x10);               //rol rax, 0x10
        rax ^= r9;              //xor rax, r9
        rax = _byteswap_uint64(rax);            //bswap rax
        rdx *= read<uintptr_t>(rax + 0x11);             //imul rdx, [rax+0x11]
        return rdx;
    }
    case 5:
    {
        r10 = read<uintptr_t>(oBaseAddress + 0x95041FC);              //mov r10, [0x00000000070C0615]
        rax = oBaseAddress;           //lea rax, [0xFFFFFFFFFDBBC24C]
        rdx += rax;             //add rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x19;           //shr rax, 0x19
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x32;           //shr rax, 0x32
        rdx ^= rax;             //xor rdx, rax
        rax = 0;                //and rax, 0xFFFFFFFFC0000000
        rax = _rotl64(rax, 0x10);               //rol rax, 0x10
        rax ^= r10;             //xor rax, r10
        rax = _byteswap_uint64(rax);            //bswap rax
        rcx = read<uintptr_t>(rax + 0x11);              //mov rcx, [rax+0x11]
        rax = r11;              //mov rax, r11
        uintptr_t RSP_0x48;
        RSP_0x48 = oBaseAddress + 0x598F00A5;                 //lea rax, [0x00000000574AC464] : RSP+0x48
        rax *= RSP_0x48;                //imul rax, [rsp+0x48]
        rax -= oBaseAddress;          //sub rax, [rsp+0xA0] -- didn't find trace -> use base
        rdx += rax;             //add rdx, rax
        rax = 0xC6D870371839E04D;               //mov rax, 0xC6D870371839E04D
        rdx *= rax;             //imul rdx, rax
        rax = 0x2435BC22D4E2922B;               //mov rax, 0x2435BC22D4E2922B
        rdx -= rax;             //sub rdx, rax
        rdx *= rcx;             //imul rdx, rcx
        rax = 0xBBD9DF3CECEEFE74;               //mov rax, 0xBBD9DF3CECEEFE74
        rdx ^= rax;             //xor rdx, rax
        rax = 0x23B4F504FA125955;               //mov rax, 0x23B4F504FA125955
        rdx *= rax;             //imul rdx, rax
        return rdx;
    }
    case 6:
    {
        r10 = read<uintptr_t>(oBaseAddress + 0x95041FC);              //mov r10, [0x00000000070C01D9]
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rax = r11;              //mov rax, r11
        rax -= oBaseAddress;          //sub rax, [rsp+0xA0] -- didn't find trace -> use base
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rax += 0xFFFFFFFFA7D1474C;              //add rax, 0xFFFFFFFFA7D1474C
        rdx += rax;             //add rdx, rax
        rcx ^= r10;             //xor rcx, r10
        rcx = _byteswap_uint64(rcx);            //bswap rcx
        rdx *= read<uintptr_t>(rcx + 0x11);             //imul rdx, [rcx+0x11]
        rax = 0xFFFFFFFFC0CD4EE3;               //mov rax, 0xFFFFFFFFC0CD4EE3
        rax -= r11;             //sub rax, r11
        rax -= oBaseAddress;          //sub rax, [rsp+0xA0] -- didn't find trace -> use base
        rdx += rax;             //add rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x23;           //shr rax, 0x23
        rax ^= rdx;             //xor rax, rdx
        rdx = 0x5A8397EF69EB3410;               //mov rdx, 0x5A8397EF69EB3410
        rax += r11;             //add rax, r11
        rax += rdx;             //add rax, rdx
        rdx = oBaseAddress;           //lea rdx, [0xFFFFFFFFFDBBBCE6]
        rdx += rax;             //add rdx, rax
        rax = 0x94B908816CF2DBE1;               //mov rax, 0x94B908816CF2DBE1
        rdx *= rax;             //imul rdx, rax
        return rdx;
    }
    case 7:
    {
        r10 = read<uintptr_t>(oBaseAddress + 0x95041FC);              //mov r10, [0x00000000070BFDC8]
        r15 = oBaseAddress + 0x6B60;          //lea r15, [0xFFFFFFFFFDBC2719]
        rax = oBaseAddress;           //lea rax, [0xFFFFFFFFFDBBB8CF]
        rax += 0xC77B;          //add rax, 0xC77B
        rax += r11;             //add rax, r11
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x9;            //shr rax, 0x09
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x12;           //shr rax, 0x12
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x24;           //shr rax, 0x24
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x13;           //shr rax, 0x13
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x26;           //shr rax, 0x26
        rdx ^= rax;             //xor rdx, rax
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r10;             //xor rcx, r10
        rax = r15;              //mov rax, r15
        rax = ~rax;             //not rax
        rax *= r11;             //imul rax, r11
        rcx = _byteswap_uint64(rcx);            //bswap rcx
        rdx += rax;             //add rdx, rax
        rax = 0x3BAB7EE1C2FB5485;               //mov rax, 0x3BAB7EE1C2FB5485
        rdx *= read<uintptr_t>(rcx + 0x11);             //imul rdx, [rcx+0x11]
        rdx += rax;             //add rdx, rax
        rax = 0xD64310FF7669DED5;               //mov rax, 0xD64310FF7669DED5
        rdx *= rax;             //imul rdx, rax
        rax = 0xC9A0080E2B52320A;               //mov rax, 0xC9A0080E2B52320A
        rdx ^= rax;             //xor rdx, rax
        return rdx;
    }
    case 8:
    {
        r10 = read<uintptr_t>(oBaseAddress + 0x95041FC);              //mov r10, [0x00000000070BF7F5]
        rax = r11;              //mov rax, r11
        rax -= oBaseAddress;          //sub rax, [rsp+0xA0] -- didn't find trace -> use base
        rax += 0xFFFFFFFF954B94E9;              //add rax, 0xFFFFFFFF954B94E9
        rdx += rax;             //add rdx, rax
        rax = 0;                //and rax, 0xFFFFFFFFC0000000
        rax = _rotl64(rax, 0x10);               //rol rax, 0x10
        rax ^= r10;             //xor rax, r10
        rax = _byteswap_uint64(rax);            //bswap rax
        rdx *= read<uintptr_t>(rax + 0x11);             //imul rdx, [rax+0x11]
        rax = rdx;              //mov rax, rdx
        rax >>= 0xE;            //shr rax, 0x0E
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x1C;           //shr rax, 0x1C
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x38;           //shr rax, 0x38
        rdx ^= rax;             //xor rdx, rax
        rax = 0x28853EAC80AAB90;                //mov rax, 0x28853EAC80AAB90
        rdx -= rax;             //sub rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x21;           //shr rax, 0x21
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0xB;            //shr rax, 0x0B
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x16;           //shr rax, 0x16
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x2C;           //shr rax, 0x2C
        rdx ^= rax;             //xor rdx, rax
        rax = 0x9ED615C5A516F48D;               //mov rax, 0x9ED615C5A516F48D
        rdx *= rax;             //imul rdx, rax
        rax = 0x4A5451CFD1051B0F;               //mov rax, 0x4A5451CFD1051B0F
        rdx *= rax;             //imul rdx, rax
        return rdx;
    }
    case 9:
    {
        r10 = read<uintptr_t>(oBaseAddress + 0x95041FC);              //mov r10, [0x00000000070BF2DC]
        r13 = oBaseAddress + 0x9F7F;          //lea r13, [0xFFFFFFFFFDBC504C]
        rcx = oBaseAddress + 0x590B7B0F;              //lea rcx, [0x0000000056C72B67]
        rax = rdx;              //mov rax, rdx
        rax >>= 0x25;           //shr rax, 0x25
        rdx ^= rax;             //xor rdx, rax
        rax = 0;                //and rax, 0xFFFFFFFFC0000000
        rax = _rotl64(rax, 0x10);               //rol rax, 0x10
        rax ^= r10;             //xor rax, r10
        rax = _byteswap_uint64(rax);            //bswap rax
        rdx *= read<uintptr_t>(rax + 0x11);             //imul rdx, [rax+0x11]
        rax = 0xE41AAE0B4978C7A7;               //mov rax, 0xE41AAE0B4978C7A7
        rdx *= rax;             //imul rdx, rax
        rax = 0x4884ED1EDA36D9B2;               //mov rax, 0x4884ED1EDA36D9B2
        rdx -= rax;             //sub rdx, rax
        rax = r11;              //mov rax, r11
        rax ^= r13;             //xor rax, r13
        rdx ^= rax;             //xor rdx, rax
        rax = 0xA5F46429036B04E5;               //mov rax, 0xA5F46429036B04E5
        rdx *= rax;             //imul rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x27;           //shr rax, 0x27
        rdx ^= rax;             //xor rdx, rax
        rdx -= r11;             //sub rdx, r11
        rdx += rcx;             //add rdx, rcx
        return rdx;
    }
    case 10:
    {
        r9 = read<uintptr_t>(oBaseAddress + 0x95041FC);               //mov r9, [0x00000000070BEE4E]
        rdx -= oBaseAddress;          //sub rdx, [rsp+0xA0] -- didn't find trace -> use base
        rax = 0;                //and rax, 0xFFFFFFFFC0000000
        rax = _rotl64(rax, 0x10);               //rol rax, 0x10
        rax ^= r9;              //xor rax, r9
        rax = _byteswap_uint64(rax);            //bswap rax
        rdx *= read<uintptr_t>(rax + 0x11);             //imul rdx, [rax+0x11]
        rax = r11;              //mov rax, r11
        rax -= oBaseAddress;          //sub rax, [rsp+0xA0] -- didn't find trace -> use base
        rax += 0xFFFFFFFFFFFF88EC;              //add rax, 0xFFFFFFFFFFFF88EC
        rdx += rax;             //add rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x12;           //shr rax, 0x12
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x24;           //shr rax, 0x24
        rdx ^= rax;             //xor rdx, rax
        rax = 0x4DBC160E13E56349;               //mov rax, 0x4DBC160E13E56349
        rdx *= rax;             //imul rdx, rax
        rax = oBaseAddress;           //lea rax, [0xFFFFFFFFFDBBAB24]
        rdx ^= rax;             //xor rdx, rax
        rax = oBaseAddress;           //lea rax, [0xFFFFFFFFFDBBA9F6]
        rdx += rax;             //add rdx, rax
        return rdx;
    }
    case 11:
    {
        r10 = read<uintptr_t>(oBaseAddress + 0x95041FC);              //mov r10, [0x00000000070BE9A8]
        rax = 0;                //and rax, 0xFFFFFFFFC0000000
        rax = _rotl64(rax, 0x10);               //rol rax, 0x10
        rax ^= r10;             //xor rax, r10
        rax = _byteswap_uint64(rax);            //bswap rax
        rdx *= read<uintptr_t>(rax + 0x11);             //imul rdx, [rax+0x11]
        rax = oBaseAddress + 0x73A4FAE9;              //lea rax, [0x0000000071609FCD]
        rax = ~rax;             //not rax
        rdx -= r11;             //sub rdx, r11
        rdx += rax;             //add rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x16;           //shr rax, 0x16
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x2C;           //shr rax, 0x2C
        rdx ^= rax;             //xor rdx, rax
        rax = 0x861DF3431C84C629;               //mov rax, 0x861DF3431C84C629
        rdx *= rax;             //imul rdx, rax
        rax = 0x714B44E8CE73C4F0;               //mov rax, 0x714B44E8CE73C4F0
        rdx -= rax;             //sub rdx, rax
        rax = oBaseAddress;           //lea rax, [0xFFFFFFFFFDBBA448]
        rcx = rax * 0xFFFFFFFFFFFFFFFE;                 //imul rcx, rax, 0xFFFFFFFFFFFFFFFE
        rax = 0x6F9175143B9ED737;               //mov rax, 0x6F9175143B9ED737
        rdx += rax;             //add rdx, rax
        rdx += rcx;             //add rdx, rcx
        return rdx;
    }
    case 12:
    {
        r10 = read<uintptr_t>(oBaseAddress + 0x95041FC);              //mov r10, [0x00000000070BE5E9]
        r15 = oBaseAddress + 0xD3DA;          //lea r15, [0xFFFFFFFFFDBC77B4]
        rcx = r11;              //mov rcx, r11
        rcx = ~rcx;             //not rcx
        rax = oBaseAddress + 0x1F86111B;              //lea rax, [0x000000001D41B1B8]
        rax = ~rax;             //not rax
        rcx *= rax;             //imul rcx, rax
        rax = r15;              //mov rax, r15
        rax -= r11;             //sub rax, r11
        rax += rdx;             //add rax, rdx
        rdx = rcx;              //mov rdx, rcx
        rdx ^= rax;             //xor rdx, rax
        rax = 0;                //and rax, 0xFFFFFFFFC0000000
        rax = _rotl64(rax, 0x10);               //rol rax, 0x10
        rax ^= r10;             //xor rax, r10
        rax = _byteswap_uint64(rax);            //bswap rax
        rdx *= read<uintptr_t>(rax + 0x11);             //imul rdx, [rax+0x11]
        rcx = oBaseAddress;           //lea rcx, [0xFFFFFFFFFDBBA24D]
        rax = r11;              //mov rax, r11
        rax -= rcx;             //sub rax, rcx
        rcx = rax + 0xffffffffca7be9d9;                 //lea rcx, [rax-0x35841627]
        rcx += rdx;             //add rcx, rdx
        rax = rcx;              //mov rax, rcx
        rax >>= 0x18;           //shr rax, 0x18
        rcx ^= rax;             //xor rcx, rax
        rax = 0xFBA7ABC8BBB4629D;               //mov rax, 0xFBA7ABC8BBB4629D
        rdx = rcx;              //mov rdx, rcx
        rdx >>= 0x30;           //shr rdx, 0x30
        rdx ^= rcx;             //xor rdx, rcx
        rdx *= rax;             //imul rdx, rax
        rax = 0x1FE6307AA1F54B4D;               //mov rax, 0x1FE6307AA1F54B4D
        rdx *= rax;             //imul rdx, rax
        rax = 0x57A7A919AF723E1B;               //mov rax, 0x57A7A919AF723E1B
        rdx -= rax;             //sub rdx, rax
        return rdx;
    }
    case 13:
    {
        r9 = read<uintptr_t>(oBaseAddress + 0x95041FC);               //mov r9, [0x00000000070BE1EF]
        rax = rdx;              //mov rax, rdx
        rax >>= 0x1A;           //shr rax, 0x1A
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x34;           //shr rax, 0x34
        rdx ^= rax;             //xor rdx, rax
        rax = 0x525F068BC2643DF7;               //mov rax, 0x525F068BC2643DF7
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0xD;            //shr rax, 0x0D
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x1A;           //shr rax, 0x1A
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x34;           //shr rax, 0x34
        rdx ^= rax;             //xor rdx, rax
        rax = 0;                //and rax, 0xFFFFFFFFC0000000
        rax = _rotl64(rax, 0x10);               //rol rax, 0x10
        rax ^= r9;              //xor rax, r9
        rax = _byteswap_uint64(rax);            //bswap rax
        rdx *= read<uintptr_t>(rax + 0x11);             //imul rdx, [rax+0x11]
        rax = 0x75DFF140FA1FB5BC;               //mov rax, 0x75DFF140FA1FB5BC
        rdx += rax;             //add rdx, rax
        rax = oBaseAddress;           //lea rax, [0xFFFFFFFFFDBB9C26]
        rdx += rax;             //add rdx, rax
        rax = 0xE5945E699002C625;               //mov rax, 0xE5945E699002C625
        rdx *= rax;             //imul rdx, rax
        rax = oBaseAddress;           //lea rax, [0xFFFFFFFFFDBB9C0E]
        rdx ^= rax;             //xor rdx, rax
        return rdx;
    }
    case 14:
    {
        r10 = read<uintptr_t>(oBaseAddress + 0x95041FC);              //mov r10, [0x00000000070BDD8A]
        r15 = oBaseAddress + 0x73A4A654;              //lea r15, [0x00000000716041CF]
        rax = 0x75736E13202430E1;               //mov rax, 0x75736E13202430E1
        rdx *= rax;             //imul rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x26;           //shr rax, 0x26
        rdx ^= rax;             //xor rdx, rax
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r10;             //xor rcx, r10
        rcx = _byteswap_uint64(rcx);            //bswap rcx
        rdx *= read<uintptr_t>(rcx + 0x11);             //imul rdx, [rcx+0x11]
        rax = rdx;              //mov rax, rdx
        rax >>= 0x9;            //shr rax, 0x09
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x12;           //shr rax, 0x12
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x24;           //shr rax, 0x24
        rdx ^= rax;             //xor rdx, rax
        rdx += r11;             //add rdx, r11
        rax = r11;              //mov rax, r11
        rax = ~rax;             //not rax
        rax *= r15;             //imul rax, r15
        rdx ^= rax;             //xor rdx, rax
        rax = 0xABD8E138F25E5687;               //mov rax, 0xABD8E138F25E5687
        rdx ^= rax;             //xor rdx, rax
        return rdx;
    }
    case 15:
    {
        r10 = read<uintptr_t>(oBaseAddress + 0x95041FC);              //mov r10, [0x00000000070BD9D9]
        rsi = 0xB656FAE057EB613B;               //mov rsi, 0xB656FAE057EB613B
        rdx *= rsi;             //imul rdx, rsi
        rax = rdx;              //mov rax, rdx
        rax >>= 0x21;           //shr rax, 0x21
        rdx ^= rax;             //xor rdx, rax
        rax = 0;                //and rax, 0xFFFFFFFFC0000000
        rax = _rotl64(rax, 0x10);               //rol rax, 0x10
        rax ^= r10;             //xor rax, r10
        rax = _byteswap_uint64(rax);            //bswap rax
        rdx *= read<uintptr_t>(rax + 0x11);             //imul rdx, [rax+0x11]
        rax = 0x5CA0A4447C245D90;               //mov rax, 0x5CA0A4447C245D90
        rdx -= rax;             //sub rdx, rax
        rdx -= r11;             //sub rdx, r11
        rax = 0xF071D0312866EB9D;               //mov rax, 0xF071D0312866EB9D
        rdx *= rax;             //imul rdx, rax
        rax = 0xFFFFFFFFFFFFF34A;               //mov rax, 0xFFFFFFFFFFFFF34A
        rax -= r11;             //sub rax, r11
        rax -= oBaseAddress;          //sub rax, [rsp+0xA0] -- didn't find trace -> use base
        rdx += rax;             //add rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x21;           //shr rax, 0x21
        rdx ^= rax;             //xor rdx, rax
        return rdx;
    }
    }
}
uint16_t get_bone_index(uint32_t bone_index)
{
    const uint64_t mb = oBaseAddress;
    uint64_t rax = mb, rbx = mb, rcx = mb, rdx = mb, rdi = mb, rsi = mb, r8 = mb, r9 = mb, r10 = mb, r11 = mb, r12 = mb, r13 = mb, r14 = mb, r15 = mb;
    rdi = bone_index;
    rcx = rdi * 0x13C8;
    rax = 0xD73F3E9D2DBEC8E7;               //mov rax, 0xD73F3E9D2DBEC8E7
    rax = _umul128(rax, rcx, (uintptr_t*)&rdx);             //mul rcx
    r11 = 0xCCCCCCCCCCCCCCCD;               //mov r11, 0xCCCCCCCCCCCCCCCD
    rbx = oBaseAddress;           //lea rbx, [0xFFFFFFFFFD6C74CB]
    rdx >>= 0xD;            //shr rdx, 0x0D
    r10 = 0xE98285CCFA0AE387;               //mov r10, 0xE98285CCFA0AE387
    rax = rdx * 0x260F;             //imul rax, rdx, 0x260F
    rcx -= rax;             //sub rcx, rax
    rax = 0xC388D5333BAA90CD;               //mov rax, 0xC388D5333BAA90CD
    r8 = rcx * 0x260F;              //imul r8, rcx, 0x260F
    rax = _umul128(rax, r8, (uintptr_t*)&rdx);              //mul r8
    rax = r8;               //mov rax, r8
    rax -= rdx;             //sub rax, rdx
    rax >>= 0x1;            //shr rax, 0x01
    rax += rdx;             //add rax, rdx
    rax >>= 0xE;            //shr rax, 0x0E
    rax = rax * 0x4892;             //imul rax, rax, 0x4892
    r8 -= rax;              //sub r8, rax
    rax = r11;              //mov rax, r11
    rax = _umul128(rax, r8, (uintptr_t*)&rdx);              //mul r8
    rax = 0xBAA551EE51D6FD2D;               //mov rax, 0xBAA551EE51D6FD2D
    rdx >>= 0x3;            //shr rdx, 0x03
    rcx = rdx + rdx * 4;            //lea rcx, [rdx+rdx*4]
    rax = _umul128(rax, r8, (uintptr_t*)&rdx);              //mul r8
    rdx >>= 0xB;            //shr rdx, 0x0B
    rax = rdx + rcx * 2;            //lea rax, [rdx+rcx*2]
    rcx = rax * 0x15F2;             //imul rcx, rax, 0x15F2
    rax = r8 * 0x15F4;              //imul rax, r8, 0x15F4
    rax -= rcx;             //sub rax, rcx
    rax = read<uint16_t>(rax + rbx * 1 + 0x95EADB0);                //movzx eax, word ptr [rax+rbx*1+0x95EADB0]
    r8 = rax * 0x13C8;              //imul r8, rax, 0x13C8
    rax = r10;              //mov rax, r10
    rax = _umul128(rax, r8, (uintptr_t*)&rdx);              //mul r8
    rax = r10;              //mov rax, r10
    rdx >>= 0xD;            //shr rdx, 0x0D
    rcx = rdx * 0x2315;             //imul rcx, rdx, 0x2315
    r8 -= rcx;              //sub r8, rcx
    r9 = r8 * 0x351B;               //imul r9, r8, 0x351B
    rax = _umul128(rax, r9, (uintptr_t*)&rdx);              //mul r9
    rax = r11;              //mov rax, r11
    rdx >>= 0xD;            //shr rdx, 0x0D
    rcx = rdx * 0x2315;             //imul rcx, rdx, 0x2315
    r9 -= rcx;              //sub r9, rcx
    rax = _umul128(rax, r9, (uintptr_t*)&rdx);              //mul r9
    rax = 0x18AB083902BDAB95;               //mov rax, 0x18AB083902BDAB95
    rdx >>= 0x4;            //shr rdx, 0x04
    rcx = rdx + rdx * 4;            //lea rcx, [rdx+rdx*4]
    rax = _umul128(rax, r9, (uintptr_t*)&rdx);              //mul r9
    rax = r9;               //mov rax, r9
    rax -= rdx;             //sub rax, rdx
    rax >>= 0x1;            //shr rax, 0x01
    rax += rdx;             //add rax, rdx
    rax >>= 0x8;            //shr rax, 0x08
    rax = rax + rcx * 4;            //lea rax, [rax+rcx*4]
    rcx = rax * 0x3A6;              //imul rcx, rax, 0x3A6
    rax = r9 * 0x3A8;               //imul rax, r9, 0x3A8
    rax -= rcx;             //sub rax, rcx
    r12 = read<uint16_t>(rax + rbx * 1 + 0x95F8930);                //movsx r12d, word ptr [rax+rbx*1+0x95F8930]
    return r12;
}