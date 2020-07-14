#include <jailhouse/types.h>
#include <jailhouse/cell-config.h>
struct { 
	struct jailhouse_system header; 
	__u64 cpus[1];
	struct jailhouse_memory mem_regions[77];
	struct jailhouse_irqchip irqchips[6];
	struct jailhouse_pci_device pci_devices[2];
} __attribute__((packed)) config = {

.header = {
	.signature = JAILHOUSE_SYSTEM_SIGNATURE,
	.revision = JAILHOUSE_CONFIG_REVISION,
	.flags = JAILHOUSE_SYS_VIRTUAL_DEBUG_CONSOLE,
	.hypervisor_memory = {
		.phys_start = 0xe2fd2000,
		.size = 0x1000000,
	},

	.debug_console = {
		.address = 0xfe215040,
		.size = 0x40,
		.type = JAILHOUSE_CON_TYPE_8250,
		.flags = JAILHOUSE_CON_ACCESS_MMIO | JAILHOUSE_CON_REGDIST_4,
	},

	.platform_info = {
		.pci_mmconfig_end_bus = 0,
		.pci_is_virtual = 1,
		.pci_domain = 1,
		.arm = {
			.maintenance_irq = 25,
			.gic_version = 2,
			.gicd_base = 4286844928,
			.gicc_base = 4286849024,
			.gich_base = 4286857216,
			.gicv_base = 4286865408,
			.gicr_base = 0,
		},

	},

	.root_cell = {
		.name = "root" ,
		.vpci_irq_base = 177,
		.num_memory_regions = ARRAY_SIZE(config.mem_regions),
		.num_pci_devices = ARRAY_SIZE(config.pci_devices),
		.cpu_set_size = sizeof(config.cpus),
		.num_irqchips = ARRAY_SIZE(config.irqchips),
	},
	},
	.cpus = {0b1111},
	
	.mem_regions = {
	/*Main Memory 0xf4000000-0xfc000000*/	{
		.phys_start = 0xf4000000,
		.virt_start = 0x0,
		.size = 0x8000000,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_EXECUTE,
	},
	/*net1_0 0xf3fff000-0xf4000000*/	{
		.phys_start = 0xf3fff000,
		.virt_start = 0x8000000,
		.size = 0x1000,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_ROOTSHARED,
	},
	/* empty optional region */ { 0 },
	/*net1_2 0xf3ffe000-0xf3fff000*/	{
		.phys_start = 0xf3ffe000,
		.virt_start = 0x8001000,
		.size = 0x1000,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_ROOTSHARED|JAILHOUSE_MEM_WRITE,
	},
	/*net1_3 0xf3ffd000-0xf3ffe000*/	{
		.phys_start = 0xf3ffd000,
		.virt_start = 0x8002000,
		.size = 0x1000,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_ROOTSHARED,
	},
	/*net2_0 0xf3ffc000-0xf3ffd000*/	{
		.phys_start = 0xf3ffc000,
		.virt_start = 0x8003000,
		.size = 0x1000,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_ROOTSHARED,
	},
	/* empty optional region */ { 0 },
	/*net2_2 0xf3ffb000-0xf3ffc000*/	{
		.phys_start = 0xf3ffb000,
		.virt_start = 0x8004000,
		.size = 0x1000,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_ROOTSHARED|JAILHOUSE_MEM_WRITE,
	},
	/*net2_3 0xf3ffa000-0xf3ffb000*/	{
		.phys_start = 0xf3ffa000,
		.virt_start = 0x8005000,
		.size = 0x1000,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_ROOTSHARED,
	},
	/*memreserve 0x3b400000-0x40000000*/	{
		.phys_start = 0x3b400000,
		.virt_start = 0x3b400000,
		.size = 0x4c00000,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_EXECUTE,
	},
	/*memory@0 0x0-0x3b400000*/	{
		.phys_start = 0x0,
		.virt_start = 0x0,
		.size = 0x3b400000,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_EXECUTE,
	},
	/*memory@0.0 0x40000000-0xfc000000*/	{
		.phys_start = 0x40000000,
		.virt_start = 0x40000000,
		.size = 0xbc000000,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_EXECUTE,
	},
	/*v3d@7ec04000 0xfec00000-0xfec04000*/	{
		.phys_start = 0xfec00000,
		.virt_start = 0xfec00000,
		.size = 0x4000,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*v3d@7ec04000.0 0xfec04000-0xfec08000*/	{
		.phys_start = 0xfec04000,
		.virt_start = 0xfec04000,
		.size = 0x4000,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*i2c@7e205000 0xfe205000-0xfe205200*/	{
		.phys_start = 0xfe205000,
		.virt_start = 0xfe205000,
		.size = 0x200,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*i2c@7e804000 0xfe804000-0xfe805000*/	{
		.phys_start = 0xfe804000,
		.virt_start = 0xfe804000,
		.size = 0x1000,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*mmc@7e300000 0xfe300000-0xfe300100*/	{
		.phys_start = 0xfe300000,
		.virt_start = 0xfe300000,
		.size = 0x100,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*local_intc@40000000 0xff800000-0xff800100*/	{
		.phys_start = 0xff800000,
		.virt_start = 0xff800000,
		.size = 0x100,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*spi@7e204600 0xfe204600-0xfe204800*/	{
		.phys_start = 0xfe204600,
		.virt_start = 0xfe204600,
		.size = 0x200,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*spi@7e2150c0 0xfe2150c0-0xfe215100*/	{
		.phys_start = 0xfe2150c0,
		.virt_start = 0xfe2150c0,
		.size = 0x40,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*pwm@7e20c000 0xfe20c000-0xfe20c028*/	{
		.phys_start = 0xfe20c000,
		.virt_start = 0xfe20c000,
		.size = 0x28,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*thermal@7d5d2200 0xfd5d2200-0xfd5d222c*/	{
		.phys_start = 0xfd5d2200,
		.virt_start = 0xfd5d2200,
		.size = 0x2c,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*usb@7e980000 0xfe980000-0xfe990000*/	{
		.phys_start = 0xfe980000,
		.virt_start = 0xfe980000,
		.size = 0x10000,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*usb@7e980000.0 0xfe00b200-0xfe01b200*/	{
		.phys_start = 0xfe00b200,
		.virt_start = 0xfe00b200,
		.size = 0x10000,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*i2c@7e205c00 0xfe205c00-0xfe205e00*/	{
		.phys_start = 0xfe205c00,
		.virt_start = 0xfe205c00,
		.size = 0x200,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*serial@7e215040 0xfe215040-0xfe215080*/	{
		.phys_start = 0xfe215040,
		.virt_start = 0xfe215040,
		.size = 0x40,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*dma@7e007000 0xfe007000-0xfe007b00*/	{
		.phys_start = 0xfe007000,
		.virt_start = 0xfe007000,
		.size = 0xb00,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*serial@7e201400 0xfe201400-0xfe201600*/	{
		.phys_start = 0xfe201400,
		.virt_start = 0xfe201400,
		.size = 0x200,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*serial@7e201800 0xfe201800-0xfe201a00*/	{
		.phys_start = 0xfe201800,
		.virt_start = 0xfe201800,
		.size = 0x200,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*cprman@7e101000 0xfe101000-0xfe103000*/	{
		.phys_start = 0xfe101000,
		.virt_start = 0xfe101000,
		.size = 0x2000,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*pixelvalve@7e807000 0xfe807000-0xfe807100*/	{
		.phys_start = 0xfe807000,
		.virt_start = 0xfe807000,
		.size = 0x100,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*dpi@7e208000 0xfe208000-0xfe20808c*/	{
		.phys_start = 0xfe208000,
		.virt_start = 0xfe208000,
		.size = 0x8c,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*serial@7e201000 0xfe201000-0xfe201200*/	{
		.phys_start = 0xfe201000,
		.virt_start = 0xfe201000,
		.size = 0x200,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*csi@7e800000 0xfe800000-0xfe800800*/	{
		.phys_start = 0xfe800000,
		.virt_start = 0xfe800000,
		.size = 0x800,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*csi@7e800000.0 0xfe802000-0xfe802800*/	{
		.phys_start = 0xfe802000,
		.virt_start = 0xfe802000,
		.size = 0x800,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*txp@7e004000 0xfe004000-0xfe004020*/	{
		.phys_start = 0xfe004000,
		.virt_start = 0xfe004000,
		.size = 0x20,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*i2c@7e205a00 0xfe205a00-0xfe205c00*/	{
		.phys_start = 0xfe205a00,
		.virt_start = 0xfe205a00,
		.size = 0x200,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*axiperf 0xfe009800-0xfe009900*/	{
		.phys_start = 0xfe009800,
		.virt_start = 0xfe009800,
		.size = 0x100,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*axiperf.0 0xfee08000-0xfee08100*/	{
		.phys_start = 0xfee08000,
		.virt_start = 0xfee08000,
		.size = 0x100,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*i2c@7e805000 0xfe805000-0xfe806000*/	{
		.phys_start = 0xfe805000,
		.virt_start = 0xfe805000,
		.size = 0x1000,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*i2s@7e203000 0xfe203000-0xfe203024*/	{
		.phys_start = 0xfe203000,
		.virt_start = 0xfe203000,
		.size = 0x24,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*aux@7e215000 0xfe215000-0xfe215008*/	{
		.phys_start = 0xfe215000,
		.virt_start = 0xfe215000,
		.size = 0x8,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*csi@7e801000 0xfe801000-0xfe801800*/	{
		.phys_start = 0xfe801000,
		.virt_start = 0xfe801000,
		.size = 0x800,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*serial@7e201600 0xfe201600-0xfe201800*/	{
		.phys_start = 0xfe201600,
		.virt_start = 0xfe201600,
		.size = 0x200,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*vec@7e806000 0xfe806000-0xfe807000*/	{
		.phys_start = 0xfe806000,
		.virt_start = 0xfe806000,
		.size = 0x1000,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*pwm@7e20c800 0xfe20c800-0xfe20c828*/	{
		.phys_start = 0xfe20c800,
		.virt_start = 0xfe20c800,
		.size = 0x28,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*spi@7e215080 0xfe215080-0xfe2150c0*/	{
		.phys_start = 0xfe215080,
		.virt_start = 0xfe215080,
		.size = 0x40,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*spi@7e204800 0xfe204800-0xfe204a00*/	{
		.phys_start = 0xfe204800,
		.virt_start = 0xfe204800,
		.size = 0x200,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*hvs@7e400000 0xfe400000-0xfe406000*/	{
		.phys_start = 0xfe400000,
		.virt_start = 0xfe400000,
		.size = 0x6000,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*rng@7e104000 0xfe104000-0xfe104010*/	{
		.phys_start = 0xfe104000,
		.virt_start = 0xfe104000,
		.size = 0x10,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*dsi@7e209000 0xfe209000-0xfe209078*/	{
		.phys_start = 0xfe209000,
		.virt_start = 0xfe209000,
		.size = 0x78,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*emmc2@7e340000 0xfe340000-0xfe340100*/	{
		.phys_start = 0xfe340000,
		.virt_start = 0xfe340000,
		.size = 0x100,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*spi@7e204a00 0xfe204a00-0xfe204c00*/	{
		.phys_start = 0xfe204a00,
		.virt_start = 0xfe204a00,
		.size = 0x200,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*hdmi@7e902000 0xfe902000-0xfe902600*/	{
		.phys_start = 0xfe902000,
		.virt_start = 0xfe902000,
		.size = 0x600,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*hdmi@7e902000.0 0xfe808000-0xfe808600*/	{
		.phys_start = 0xfe808000,
		.virt_start = 0xfe808000,
		.size = 0x600,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*pixelvalve@7e207000 0xfe207000-0xfe207100*/	{
		.phys_start = 0xfe207000,
		.virt_start = 0xfe207000,
		.size = 0x100,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*i2c@7e205800 0xfe205800-0xfe205a00*/	{
		.phys_start = 0xfe205800,
		.virt_start = 0xfe205800,
		.size = 0x200,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*pixelvalve@7e206000 0xfe206000-0xfe206100*/	{
		.phys_start = 0xfe206000,
		.virt_start = 0xfe206000,
		.size = 0x100,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*smi@7e600000 0xfe600000-0xfe600100*/	{
		.phys_start = 0xfe600000,
		.virt_start = 0xfe600000,
		.size = 0x100,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*serial@7e201a00 0xfe201a00-0xfe201c00*/	{
		.phys_start = 0xfe201a00,
		.virt_start = 0xfe201a00,
		.size = 0x200,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*dsi@7e700000 0xfe700000-0xfe70008c*/	{
		.phys_start = 0xfe700000,
		.virt_start = 0xfe700000,
		.size = 0x8c,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*mmc@7e202000 0xfe202000-0xfe202100*/	{
		.phys_start = 0xfe202000,
		.virt_start = 0xfe202000,
		.size = 0x100,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*watchdog@7e100000 0xfe100000-0xfe100114*/	{
		.phys_start = 0xfe100000,
		.virt_start = 0xfe100000,
		.size = 0x114,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*watchdog@7e100000.0 0xfe00a000-0xfe00a114*/	{
		.phys_start = 0xfe00a000,
		.virt_start = 0xfe00a000,
		.size = 0x114,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*watchdog@7e100000.1 0xfec11000-0xfec11114*/	{
		.phys_start = 0xfec11000,
		.virt_start = 0xfec11000,
		.size = 0x114,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*spi@7e204c00 0xfe204c00-0xfe204e00*/	{
		.phys_start = 0xfe204c00,
		.virt_start = 0xfe204c00,
		.size = 0x200,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*spi@7e204000 0xfe204000-0xfe204200*/	{
		.phys_start = 0xfe204000,
		.virt_start = 0xfe204000,
		.size = 0x200,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*gpiomem 0xfe200000-0xfe201000*/	{
		.phys_start = 0xfe200000,
		.virt_start = 0xfe200000,
		.size = 0x1000,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*i2c@7e205600 0xfe205600-0xfe205800*/	{
		.phys_start = 0xfe205600,
		.virt_start = 0xfe205600,
		.size = 0x200,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*xhci@7e9c0000 0xfe9c0000-0xfeac0000*/	{
		.phys_start = 0xfe9c0000,
		.virt_start = 0xfe9c0000,
		.size = 0x100000,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*rpivid-local-intc@7eb10000 0xfeb10000-0xfeb11000*/	{
		.phys_start = 0xfeb10000,
		.virt_start = 0xfeb10000,
		.size = 0x1000,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*h264-decoder@7eb20000 0xfeb20000-0xfeb30000*/	{
		.phys_start = 0xfeb20000,
		.virt_start = 0xfeb20000,
		.size = 0x10000,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*pcie@7d500000 0xfd500000-0xfd509310*/	{
		.phys_start = 0xfd500000,
		.virt_start = 0xfd500000,
		.size = 0x9310,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*dma@7e007b00 0xfe007b00-0xfe007f00*/	{
		.phys_start = 0xfe007b00,
		.virt_start = 0xfe007b00,
		.size = 0x400,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*genet@7d580000 0xfd580000-0xfd590000*/	{
		.phys_start = 0xfd580000,
		.virt_start = 0xfd580000,
		.size = 0x10000,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*vp9-decoder@7eb30000 0xfeb30000-0xfeb40000*/	{
		.phys_start = 0xfeb30000,
		.virt_start = 0xfeb30000,
		.size = 0x10000,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	/*hevc-decoder@7eb00000 0xfeb00000-0xfeb10000*/	{
		.phys_start = 0xfeb00000,
		.virt_start = 0xfeb00000,
		.size = 0x10000,
		.flags = JAILHOUSE_MEM_READ|JAILHOUSE_MEM_WRITE|JAILHOUSE_MEM_IO|JAILHOUSE_MEM_IO_8|JAILHOUSE_MEM_IO_16|JAILHOUSE_MEM_IO_32|JAILHOUSE_MEM_IO_64,
	},
	},
	.irqchips = {
		{
			.address = 0xff841000,
			.pin_base = 32,
			.pin_bitmap = {0x3fffffff, 0xfffffffe, 0x3fff0e7f, 0xeb6177d6},
		},
		{
			.address = 0xff841000,
			.pin_base = 160,
			.pin_bitmap = {0xe3ffffff, 0xffff3fff},
		},
		{
			.address = 0xff841000,
			.pin_base = 32,
			.pin_bitmap = {},
		},
		{
			.address = 0xff841000,
			.pin_base = 160,
			.pin_bitmap = {0x0, 0x20000},
		},
		{
			.address = 0xff841000,
			.pin_base = 32,
			.pin_bitmap = {},
		},
		{
			.address = 0xff841000,
			.pin_base = 160,
			.pin_bitmap = {0x0, 0x40000},
		},
	},

	.pci_devices = {
		/*net1*/
		{
			.type = JAILHOUSE_PCI_TYPE_IVSHMEM,
			.domain = 1,
			.bar_mask = JAILHOUSE_IVSHMEM_BAR_MASK_INTX,
			.bdf = 0 << 3,
			.shmem_regions_start = 1,
			.shmem_dev_id = 0,
			.shmem_peers = 2,
			.shmem_protocol = JAILHOUSE_SHMEM_PROTO_VETH,
		},
		/*net2*/
		{
			.type = JAILHOUSE_PCI_TYPE_IVSHMEM,
			.domain = 1,
			.bar_mask = JAILHOUSE_IVSHMEM_BAR_MASK_INTX,
			.bdf = 1 << 3,
			.shmem_regions_start = 5,
			.shmem_dev_id = 0,
			.shmem_peers = 2,
			.shmem_protocol = JAILHOUSE_SHMEM_PROTO_VETH,
		},
	},

};