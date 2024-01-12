#define __IO volatile
typedef unsigned int uint32_t;

#define	RCC 0x40023800
#define RCC_AHB1ENR (*((__IO uint32_t*)(RCC+0x30)))

typedef struct{
	__IO uint32_t MODER;
	__IO uint32_t OTYPER;
	__IO uint32_t OSPEEDR;
	__IO uint32_t PUPDR;
	__IO uint32_t IDR;
	__IO uint32_t ODR;
}GPIO_TypeDef;

#define GPIOA ((__IO GPIO_TypeDef*)0x40020000UL)
#define GPIOC ((__IO GPIO_TypeDef*)0x40020800UL)
#define GPIOB ((__IO GPIO_TypeDef*)0x40020400UL)

static void Delay(const unsigned int count){
	unsigned int index_0;
	for(index_0 = (1000*count); index_0!=0;index_0--);
}

int main(void){
	
	RCC_AHB1ENR = 0x00000007UL; //Port A,B,C enable
	
	GPIOA->MODER = 0xA8000400UL;
	GPIOA->OTYPER = 0x00000000UL;
	GPIOA->OSPEEDR =0x0C000000UL;
	GPIOA->PUPDR =0x64000000UL;
	
	GPIOB->MODER = 0x00000290UL;
	GPIOB->OTYPER = 0x00000000UL;
	GPIOB->OSPEEDR =0x000000C0UL;
	GPIOB->PUPDR =0x00000100UL;
	
	GPIOC->MODER = 0x00010000UL;
	GPIOC->OTYPER =0x00000000UL;
	GPIOC->OSPEEDR =0x00000000UL;
	GPIOC->PUPDR = 0x00000000UL;
	
	while(1){
		GPIOA->ODR = 0x00000020UL;
		Delay(500);
		GPIOA->ODR = 0x00000000UL;
		
		GPIOB->ODR = 0x00000004UL;
		Delay(500);
		GPIOB->ODR = 0x00000000UL;
	
		GPIOC->ODR = 0x00000100UL;
		Delay(500);
		GPIOC->ODR = 0x00000000UL;
	}
}
