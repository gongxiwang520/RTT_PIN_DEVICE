#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

/*
 * 程序清单：这是一个 PIN 设备使用例程
 * 例程导出了 pin_beep_sample 命令到控制终端
 * 命令调用格式：pin_beep_sample
 * 程序功能：通过按键控制蜂鸣器对应引脚的电平状态控制蜂鸣器
*/

#define BEEP_PIN    GET_PIN(C, 1)

#define KEY0_PIN    GET_PIN(C, 8)
#define KEY1_PIN    GET_PIN(C, 9)

void beep_on(void *args)
{// 开启蜂鸣器
  rt_kprintf("turn on beep!\n");
  rt_pin_write(BEEP_PIN, PIN_LOW);
}

void beep_off(void *args)
{// 关闭蜂鸣器
  rt_kprintf("turn off beep!\n");
  rt_pin_write(BEEP_PIN, PIN_HIGH);  
}

static void pin_beep_sample(void)
{
  // 蜂鸣器引脚输出模式
  rt_pin_mode(BEEP_PIN, PIN_MODE_OUTPUT);
  // 默认高电平
  rt_pin_write(BEEP_PIN, PIN_HIGH);

  // 按键0上拉输入模式
  rt_pin_mode(KEY0_PIN, PIN_MODE_INPUT_PULLUP);
  // 绑定下降沿中断回调函数
  rt_pin_attach_irq(KEY0_PIN, PIN_IRQ_MODE_FALLING, beep_on, RT_NULL);
  // 使能中断
  rt_pin_irq_enable(KEY0_PIN, PIN_IRQ_ENABLE);

  rt_pin_mode(KEY1_PIN, PIN_MODE_INPUT_PULLUP);
  rt_pin_attach_irq(KEY1_PIN, PIN_IRQ_MODE_FALLING, beep_off, RT_NULL);
  rt_pin_irq_enable(KEY1_PIN, PIN_IRQ_ENABLE);
}

MSH_CMD_EXPORT(pin_beep_sample, pin beep sample);

