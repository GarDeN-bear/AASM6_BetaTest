#include "pch.h"
#include "ErrorMessages.h"
namespace ErrMsg
{
    //Эти коды ошибок должны совпадать с аналогичными в AASM6.Lib
    extern const int ErrC_OK = 0;
    extern const int ErrC_NumberMustBeReal = 1;
    extern const int ErrC_NumberMustNotBeNeg = 2;
    extern const int ErrC_NumberOfRowsOrColumnsMustBeGE1 = 3;
    extern const int ErrC_MemAlloc = 4;
    extern const int ErrC_InterruptByUser = 5;
    extern const int ErrC_ArgMustBe0or1 = 6;
    extern const int ErrC_AngleMustBeLT90deg = 7;
    extern const int ErrC_ArgMustNotBeGT1 = 8;
    extern const int ErrC_ArgMustNotBeGTNextArg = 9;
    extern const int ErrC_ArgMustNotBeLT1 = 10;
    extern const int ErrC_ArgMustBe01or2 = 11;
    extern const int ErrC_RowCountMustBeTheSame = 12;
    extern const int ErrC_SurfMustNotIntersect = 13;
    extern const int ErrC_SurfMustNotBeOverTheZcilPart = 14;
    extern const int ErrC_SurfMustNotBeOverTheNosPart = 15;

    // Объявляем таблицу с сообщениями об ошибках
    // !!! Для того чтобы в маткаде корректно отображались сообщения на русском языке
    // !!! этот файл должен быть сохранён с кодировкой "Юникод (UTF-8, БЕЗ сигнатуры)"    
    extern const char* ErrorMessageTable[] = {
        /*0*/ /*"Нет ошибок",*/ // В отличии от CppExample, для маткада эта строка должна отсутсвовать, тогда коды будут совпадать
        /*1*/ "Число должно быть действительным",
        /*2*/ "Число не должно быть отрицательным",
        /*3*/ "Число строк/столбцов должно быть больше либо равно 1",
        /*4*/ "Ошибка выделения памяти",
        /*5*/ "Вычисление прервано пользователем",
        /*6*/ "Этот аргумент может быть равен только 0 или 1",
        /*7*/ "Угол должен быть меньше 90 градусов",
        /*8*/ "Число не должно быть больше 1",
        /*9*/ "Этот аргумент не должен быть больше следующего аргумента",
        /*10*/ "Число не должно быть меньше 1",
        /*11*/ "Этот аргумент может быть равен только 0, 1 или 2",
        /*12*/ "Количество элементов в массиве не совпадает с количеством элементов в массиве M",
        /*13*/ "Несущие поверхности не должны пересекаться",
        /*14*/ "Несущая поверхность не должна выходить за цилиндрическую часть ЛА",
        /*15*/ "Несущая поверхность не должна заходить на носовую часть ЛА"
    };
}