/*


#define __IO volatile
typedef unsigned int uint32_t;

#define	RCC 0x40023800
#define RCC_AHB1ENR (*((__IO uint32_t*)(RCC+0x30)))

#define GPIOx_MODER 0x00
#define GPIOx_OTYPER 0x04
#define GPIOx_OSPEEDR 0x08
#define GPIOx_PUPDR 0x0C
#define GPIOx_IDR 0x10
#define GPIOx_ODR 0x14



#define GPIOA 0x40020000

#define GPIOA_MODER		(*((__IO uint32_t*)(GPIOA +GPIOx_MODER)))
#define GPIOA_OTYPER	(*((__IO uint32_t*)(GPIOA +GPIOx_OTYPER)))
#define GPIOA_OSPEEDR (*((__IO uint32_t*)(GPIOA +GPIOx_OSPEEDR)))
#define GPIOA_PUPDR 	(*((__IO uint32_t*)(GPIOA +GPIOx_PUPDR)))

#define GPIOA_IDR 		(*((__IO uint32_t*)(GPIOA +GPIOx_IDR)))
#define GPIOA_ODR 		(*((__IO uint32_t*)(GPIOA +GPIOx_ODR)))
	

#define GPIOC 0x40020800

#define GPIOC_MODER 	(*((__IO uint32_t*)(GPIOC +GPIOx_MODER)))
#define GPIOC_OTYPER 	(*((__IO uint32_t*)(GPIOC +GPIOx_OTYPER)))
#define GPIOC_OSPEEDR (*((__IO uint32_t*)(GPIOC +GPIOx_OSPEEDR)))
#define GPIOC_PUPDR 	(*((__IO uint32_t*)(GPIOA +GPIOx_PUPDR)))

#define GPIOC_IDR 		(*((__IO uint32_t*)(GPIOC +GPIOx_IDR)))
#define GPIOC_ODR 		(*((__IO uint32_t*)(GPIOC +GPIOx_ODR)))

static void Delay(const unsigned int count){
	unsigned int index_0;
	for(index_0 = (1000*count); index_0!=0;index_0--);

}


int main(void){
	
	RCC_AHB1ENR = 0x00000005; //Port A, C enable
	
	GPIOA_MODER = 0xA8000400;
	GPIOA_OTYPER =0x00000000;
	GPIOA_OSPEEDR =0x0C000000;
	GPIOA_PUPDR = 0x64000000;
	
	GPIOC_MODER = 0x00010000;
	GPIOC_OTYPER =0x00000000;
	GPIOC_OSPEEDR =0x00000000;
	GPIOC_PUPDR = 0x00000000;
	
	while(1){
		
		
		GPIOA_ODR = 0x00000020;
		Delay(500);
		GPIOA_ODR = 0x00000000;
		
		GPIOC_ODR = 0x00000100;
		Delay(500);
		GPIOC_ODR = 0x00000000;
	
		
		
	}
	
}

*/
