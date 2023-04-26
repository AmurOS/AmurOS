// define VESA mode constants
#define VESA_MODE_640x480 0x101
#define VESA_MODE_800x600 0x103
#define VESA_MODE_1024x768 0x105

// VesaInfoBlock struct for holding VESA information
struct VesaInfoBlock {
    char signature[4];
    bit8 version;
    byte32i oemStringPtr;
    byte32i capabilities;
    byte32i videoModePtr;
    bit8 totalMemory;
    bit8 oemSoftwareRev;
    byte32i oemVendorNamePtr;
    byte32i oemProductNamePtr;
    byte32i oemProductRevPtr;
    char reserved[222];
    char oemData[256];
} __attribute__((packed));

// VesaModeInfoBlock struct for holding mode information
struct VesaModeInfoBlock {
    bit8 attributes;
    byte winA, winB;
    bit8 granularity;
    bit8 windowSize;
    bit8 segmentA, segmentB;
    byte32i winFuncPtr;
    bit8 pitch;
    bit8 width, height;
    byte wChar, yChar, planes, bpp, banks;
    byte memoryModel, bankSize, imagePages;
    byte reserved0;
    byte redMask, redPosition;
    byte greenMask, greenPosition;
    byte blueMask, bluePosition;
    byte rsvMask, rsvPosition;
    byte directColorAttributes;
    byte32i physbase;
    byte32i reserved1;
} __attribute__((packed));

// function to initialize VESA
void init_vesa(byte32i mode) {
    struct VesaInfoBlock *vInfo;
    struct VesaModeInfoBlock *mInfo;
    bit8 *buffer;
    byte32i vbeSignature = 0x32454256;
    byte32i vbeVersion;
    byte32i vbeFarPtr;
    byte32i vbeInterfaceSeg = 0;
    byte32i vbeInterfaceOff = 0;
    byte *regs = (byte*) 0x10;
    
    // set up registers for VESA function call
    regs[0] = 0x4F;
    regs[1] = 0x01;
    regs[2] = 0x02;
    regs[3] = 0x00;  
    regs[4] = (mode & 0xFF);
    regs[5] = ((mode >> 8) & 0xFF);
    regs[6] = 0x00;
    regs[7] = 0x00;
    
    // call VESA function using BIOS interrupt
    asm("int $0x10");
    
    // check if VESA was successfully initialized
    if(regs[0] != 0x4F) {
        return;
    }
    
    // get VESA information block
    vbeVersion = *((bit8*) 0x4F00);
    vbeFarPtr = *((byte32i*) 0x4F02);
    if(vbeVersion >= 0x200) {
        vbeInterfaceSeg = *((bit8*) 0x4F06);
        vbeInterfaceOff = *((bit8*) 0x4F08);
    }
    vInfo = (struct VesaInfoBlock*) ((vbeFarPtr >> 16) << 4 | (vbeFarPtr & 0xFFFF));
    
    // get mode information block
    mInfo = (struct VesaModeInfoBlock*) ((byte32i) vInfo->videoModePtr + 0x200000);
    
    // set video mode to specified resolution
    buffer = (bit8*) 0xA0000;
    __std__memset(buffer, 0, 65536);
    
    // add code here to draw your graphics using VESA
}