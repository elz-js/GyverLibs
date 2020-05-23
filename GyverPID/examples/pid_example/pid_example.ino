/*
   Пример работы ПИД регулятора в автоматическом режиме по встроенному таймеру
   Давайте представим, что на 3 пине у нас спираль нагрева, подключенная через мосфет,
   управляем ШИМ сигналом
   И есть какой то абстрактный датчик температуры, на который влияет спираль
*/

// перед подключением библиотеки можно добавить настройки:
// сделает часть вычислений целочисленными, что чуть (совсем чуть!) ускорит код
// #define PID_INTEGER

// режим, при котором интегральная составляющая суммируется только в пределах указанного количества значений
// #define PID_INTEGRAL_WINDOW 50
#include "GyverPID.h"

GyverPID regulator(0.1, 0.05, 0.01, 10);  // коэф. П, коэф. И, коэф. Д, период дискретизации dt (мс)
// или так:
// GyverPID regulator(0.1, 0.05, 0.01);	// можно П, И, Д, без dt, dt будет по умолч. 100 мс

void setup() {
  regulator.setDirection(NORMAL); // направление регулирования (NORMAL/REVERSE). ПО УМОЛЧАНИЮ СТОИТ NORMAL
  regulator.setLimits(0, 255);    // пределы (ставим для 8 битного ШИМ). ПО УМОЛЧАНИЮ СТОЯТ 0 И 255
  regulator.setpoint = 50;        // сообщаем регулятору температуру, которую он должен поддерживать

  // в процессе работы можно менять коэффициенты
  regulator.Kp = 5.2;
  regulator.Ki += 0.5;
  regulator.Kd = 0;
}

void loop() {
  int temp;                 // читаем с датчика температуру
  regulator.input = temp;   // сообщаем регулятору текущую температуру

  // getResultTimer возвращает значение для управляющего устройства
  // (после вызова можно получать это значение как regulator.output)
  // обновление происходит по встроенному таймеру на millis()
  analogWrite(3, regulator.getResultTimer());  // отправляем на мосфет

  // .getResultTimer() по сути возвращает regulator.output
}
