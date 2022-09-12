import ctypes

#  Подключение DLL
libstructpy = ctypes.CDLL('F:/AASM6/AASM6_Python/AASM6_DYN.dll')

ErrorMessageTable = {
    1: 'число должно быть действительным',
    2: 'число не должно быть отрицательным',
    3: 'число строк/столбцов должно быть больше либо равно 1',
    4: 'ошибка выделения памяти',
    5: 'вычисление прервано пользователем',
    6: 'этот аргумент может быть равен только 0 или 1',
    7: 'угол должен быть меньше 90 градусов',
    8: 'число не должно быть больше 1',
    9: 'этот аргумент не должен быть больше следующего аргумента',
    10: 'число не должно быть меньше 1',
    11: 'этот аргумент может быть равен только 0, 1 или 2',
    12: 'количество элементов в массиве не совпадает с количеством элементов в массиве M',
    13: 'несущие поверхности не должны пересекаться',
    14: 'несущая поверхность не должна выходить за цилиндрическую часть ЛА',
    15: 'несущая поверхность не должна заходить на носовую часть ЛА"',
}

# класс, который соответствует структуре ErrorCode (AASM6_DYN.h)


class ErrorCode(ctypes.Structure):
    _fields_ = (
        ('Code', ctypes.c_int),
        ('ArgNumber', ctypes.c_int),
    )

# класс, который соответствует структуре InputComplex (AASM6_DYN.h)


class InputComplex(ctypes.Structure):
    _fields_ = (
        ('Min', ctypes.c_float),
        ('Value', ctypes.c_float),
        ('Max', ctypes.c_float),
    )

class Vector(object):
    libstructpy.new_vector.restype = ctypes.c_void_p
    libstructpy.new_vector.argtypes = []
    libstructpy.delete_vector.restype = None
    libstructpy.delete_vector.argtypes = [ctypes.c_void_p]
    libstructpy.vector_size.restype = ctypes.c_int
    libstructpy.vector_size.argtypes = [ctypes.c_void_p]
    libstructpy.vector_get.restype = ctypes.c_float
    libstructpy.vector_get.argtypes = [ctypes.c_void_p, ctypes.c_int]
    libstructpy.vector_push_back.restype = None
    libstructpy.vector_push_back.argtypes = [ctypes.c_void_p, ctypes.c_float]


    def __init__(self, arr = None):
            # инициализация вектора
            self.vector = libstructpy.new_vector()
            
            # добавление элементов из arr в вектор
            if arr is not None:
                # проверяем, является ли arr iterable-объектом
                try:
                    iter(arr)
                except:     # иначе, когда arr является обычным числом
                    libstructpy.vector_push_back(self.vector, ctypes.c_float(arr))
                else:       # если arr - iterable-объект
                    for val in arr:
                        libstructpy.vector_push_back(self.vector, ctypes.c_float(val))

    # деструктор
    def __del__(self):
        libstructpy.delete_vector(self.vector)

    # длина элементов вектора
    def __len__(self):
        return libstructpy.vector_size(self.vector)

    # возвращает элемент вектора по индексу
    def __getitem__(self, ind):
        if 0 <= ind < len(self):
            return libstructpy.vector_get(self.vector, ctypes.c_int(ind))
        raise IndexError('Vector index out of range')

    # возвращает в виде строки список из элементов 
    def __repr__(self):
        return '[{}]'.format(', '.join(str(self[i]) for i in range(len(self))))

    # добавляет элемент в конец вектора
    def push(self, val):
        return libstructpy.vector_push_back(self.vector, ctypes.c_float(val))


def get_Cyalf_ConCil(M, lambda_nos, lambda_cil):
    """Функция для определения производной по углу атаки\\  
    коэффициента подъёмной силы изолированного фюзеляжа\\
    комбинации конус-цилиндр.

    Аргументы
    =========

        M: `float`
            Число Маха (аргумент 1).  
        lambda_nos: `float`
            Удлинение носовой части корпуса (аргумент 2).
        lambda_cil: `float`
            Удлинение цилиндрической части корпуса (аргумент 3).

    Выходные параметры
    ==================     

        'Result': `float`
            Производная по углу атаки коэффициента подъёмной силы изолированного фюзеляжа, 1/рад.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x2':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======

        >>> print('Cyalf_ConCil:')
        M = 1
        lambda_nos = 2
        lambda_cil = 1
        Cyalf_ConCil = get_Cyalf_ConCil(
            M=M, 
            lambda_nos=lambda_nos, 
            lambda_cil=lambda_cil
        )
        print(f'M = {M}')
        print(f'lambda_nos = {lambda_nos}')
        print(f'lambda_cil = {lambda_cil}')
        print('Result =', np.deg2rad(Cyalf_ConCil['Result']))
        print('x1_Min =', Cyalf_ConCil['x1']['Min'])
        print('x1_Value =', Cyalf_ConCil['x1']['Value'])
        print('x1_Max =', Cyalf_ConCil['x1']['Max'])
        print('x2_Min =', Cyalf_ConCil['x2']['Min'])
        print('x2_Value =', Cyalf_ConCil['x2']['Value'])
        print('x2_Max =', Cyalf_ConCil['x2']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_Cyalf_ConCil.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.c_float,
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_Cyalf_ConCil.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}
    res_dict['x2'] = {}
    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x2 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_Cyalf_ConCil(
        ctypes.byref(Result),
        ctypes.c_float(M),
        ctypes.c_float(lambda_nos),
        ctypes.c_float(lambda_cil),
        ctypes.byref(x2),
        ctypes.byref(x1),
    )
    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
        res_dict['x2']['Value'] = x2.Value
        res_dict['x2']['Min'] = x2.Min
        res_dict['x2']['Max'] = x2.Max
    return res_dict


def get_Cyalf_OgiCil(M, lambda_nos, lambda_cil):
    """Функция для определения производной по углу атаки\\  
    коэффициента подъёмной силы изолированного фюзеляжа\\
    комбинации оживало-цилиндр.

    Аргументы
    =========

        M: `float`
            Число Маха (аргумент 1).  
        lambda_nos: `float`
            Удлинение носовой части корпуса (аргумент 2).
        lambda_cil: `float`
            Удлинение цилиндрической части корпуса (аргумент 3).

    Выходные параметры
    ==================     

        'Result': `float`
            Производная по углу атаки коэффициента подъёмной силы изолированного фюзеляжа, 1/рад.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x2':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======

        >>> print('Cyalf_OgiCil:')
        M = 1
        lambda_nos = 2
        lambda_cil = 1
        Cyalf_OgiCil = get_Cyalf_OgiCil(
            M=M, 
            lambda_nos=lambda_nos, 
            lambda_cil=lambda_cil
        )
        print(f'M = {M}')
        print(f'lambda_nos = {lambda_nos}')
        print(f'lambda_cil = {lambda_cil}')
        print('Result =', np.deg2rad(Cyalf_OgiCil['Result']))
        print('x1_Min =', Cyalf_OgiCil['x1']['Min'])
        print('x1_Value =', Cyalf_OgiCil['x1']['Value'])
        print('x1_Max =', Cyalf_OgiCil['x1']['Max'])
        print('x2_Min =', Cyalf_OgiCil['x2']['Min'])
        print('x2_Value =', Cyalf_OgiCil['x2']['Value'])
        print('x2_Max =', Cyalf_OgiCil['x2']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_Cyalf_OgiCil.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.c_float,
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_Cyalf_OgiCil.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}
    res_dict['x2'] = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x2 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_Cyalf_OgiCil(
        ctypes.byref(Result),
        ctypes.c_float(M),
        ctypes.c_float(lambda_nos),
        ctypes.c_float(lambda_cil),
        ctypes.byref(x2),
        ctypes.byref(x1),
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
        res_dict['x2']['Value'] = x2.Value
        res_dict['x2']['Min'] = x2.Min
        res_dict['x2']['Max'] = x2.Max
    return res_dict


def get_Cyalf_SphCil(M, lambda_nos, lambda_cil):
    """Функция для определения производной по углу атаки\\  
    коэффициента подъёмной силы изолированного фюзеляжа\\
    комбинации цилиндра со сферическим затуплением и с плоским торцом.

    Аргументы
    =========

        M: `float`
            Число Маха (аргумент 1).  
        lambda_nos: `float`
            Параметр, определяющий тип носовой части (аргумент 2):
                lambda_nos = 0 - носовая часть считается плоской;\\
                lambda_nos = 1 - носовая часть считается сферической;\\
                0 < lambda_nos < 1 - осуществляется интерполяция между кривой для цилиндра с\\
                    плоским торцом и кривой для цилиндра со сферическим затуплением.
        lambda_cil: `float`

    Выходные параметры
    ==================     

        'Result': `float`
            Производная по углу атаки коэффициента подъёмной силы изолированного фюзеляжа, 1/рад.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x2':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======

        >>> print('Cyalf_SphCil:')
        M = 1
        lambda_nos = 2 
        lambda_cil = 1
        Cyalf_SphCil = get_Cyalf_SphCil(
            M=M, 
            lambda_nos=lambda_nos, 
            lambda_cil=lambda_cil
        )
        print(f'M = {M}')
        print(f'lambda_nos = {lambda_nos}')
        print(f'lambda_cil = {lambda_cil}')
        print('Result =', np.deg2rad(Cyalf_SphCil['Result']))
        print('x1_Min =', Cyalf_SphCil['x1']['Min'])
        print('x1_Value =', Cyalf_SphCil['x1']['Value'])
        print('x1_Max =', Cyalf_SphCil['x1']['Max'])
        print('x2_Min =', Cyalf_SphCil['x2']['Min'])
        print('x2_Value =', Cyalf_SphCil['x2']['Value'])
        print('x2_Max =', Cyalf_SphCil['x2']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_Cyalf_SphCil.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.c_float,
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_Cyalf_SphCil.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}
    res_dict['x2'] = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x2 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_Cyalf_SphCil(
        ctypes.byref(Result),
        ctypes.c_float(M),
        ctypes.c_float(lambda_nos),
        ctypes.c_float(lambda_cil),
        ctypes.byref(x2),
        ctypes.byref(x1),
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
        res_dict['x2']['Value'] = x2.Value
        res_dict['x2']['Min'] = x2.Min
        res_dict['x2']['Max'] = x2.Max
    return res_dict


def get_Cyalf_IsP(M, lambda_c, cc, chi_05, eta_c):
    """Функция для определения производной по углу атаки\\  
    коэффициента подъёмной силы изолированной несущей поверхности.

    Аргументы
    =========

        M: `float`
            Число Маха (аргумент 1).  
        lambda_c: `float`
            Удлинение консолей (аргумент 2).
        cc: `float`
            Относительная толщина профиля (аргумент 3).
        chi_05: `float`
            Угол стреловидности по линии середин хорд (аргумент 4).
        eta_c: `float`
            Сужение консолей (аргумент 5).

    Выходные параметры
    ==================     

        'Result': `float`
            Производная по углу атаки коэффициента подъёмной силы изолированного фюзеляжа, 1/рад.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x2':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x3':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======

        >>> print('Cyalf_IsP:')
        M = 1
        lambda_c = 0.25
        cc = 1
        chi_05 = 0
        eta_c = 1
        Cyalf_IsP = get_Cyalf_IsP(
            M=M,
            lambda_c=lambda_c,
            cc=cc,
            chi_05=chi_05,
            eta_c=eta_c
        )
        print(f'M = {M}')
        print(f'lambda_c = {lambda_c}')
        print(f'cc = {cc}')
        print(f'chi_05 = {chi_05}')
        print(f'eta_c = {eta_c}')
        print('Result =', np.deg2rad(Cyalf_IsP['Result']/lambda_c))
        print('x1_Min =', Cyalf_IsP['x1']['Min'])
        print('x1_Value =', Cyalf_IsP['x1']['Value'])
        print('x1_Max =', Cyalf_IsP['x1']['Max'])
        print('x2_Min =', Cyalf_IsP['x2']['Min'])
        print('x2_Value =', Cyalf_IsP['x2']['Value'])
        print('x2_Max =', Cyalf_IsP['x2']['Max'])
        print('x3_Min =', Cyalf_IsP['x3']['Min'])
        print('x3_Value =', Cyalf_IsP['x3']['Value'])
        print('x3_Max =', Cyalf_IsP['x3']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_Cyalf_IsP.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.c_float,
        ctypes.c_float,
        ctypes.c_float,
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_Cyalf_IsP.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}
    res_dict['x2'] = {}
    res_dict['x3'] = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x2 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x3 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_Cyalf_IsP(
        ctypes.byref(Result),
        ctypes.c_float(M),
        ctypes.c_float(lambda_c),
        ctypes.c_float(cc),
        ctypes.c_float(chi_05),
        ctypes.c_float(eta_c),
        ctypes.byref(x3),
        ctypes.byref(x2),
        ctypes.byref(x1),
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
        res_dict['x2']['Value'] = x2.Value
        res_dict['x2']['Min'] = x2.Min
        res_dict['x2']['Max'] = x2.Max
        res_dict['x3']['Value'] = x3.Value
        res_dict['x3']['Min'] = x3.Min
        res_dict['x3']['Max'] = x3.Max
    return res_dict


def get_kappa_M(M):
    """Функция для определения поправочного множителя,\\
    учитывающего влияние числа Маха при расчёте коэффициентов\\
    интерференции фюзеляжа и несущей поверхности.

    Аргументы
    =========

        M: `float`
            Число Маха (аргумент 1).  

    Выходные параметры
    ==================     

        'Result': `float`
            Поправочный множитель, учитывающего влияние\\
            числа Маха при расчёте коэффициентов интерференции\\
            фюзеляжа и несущей поверхности.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======

        >>> print('kappa_M:')
        M = 1
        kappa_M = get_kappa_M(
            M=M
        )
        print(f'M = {M}')
        print('Result =', kappa_M['Result'])
        print('x1_Min =', kappa_M['x1']['Min'])
        print('x1_Value =', kappa_M['x1']['Value'])
        print('x1_Max =', kappa_M['x1']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_kappa_M.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_kappa_M.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_kappa_M(
        ctypes.byref(Result),
        ctypes.c_float(M),
        ctypes.byref(x1),
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
    return res_dict


def get_Coordinate_zz_v(M, lambda_c, chi_05, zeta_c):
    """Функция для определения относительной поперечной координаты вихря,\\
    сбегающего с консоли несущей поверхности.

    Аргументы
    =========

        M: `float`
            Число Маха (аргумент 1).  
        lambda_c: `float`
            Удлинение консолей (аргумент 2).
        chi_05: `float`
            Угол стреловидности по линии середин хорд (аргумент 3).
        zeta_c: `float`
            Сужение консолей (аргумент 4).

    Выходные параметры
    ==================     

        'Result': `float`
            Относительная поперечная координата вихря,\\
            сбегающего с консоли несущей поверхности.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x2':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x3':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======

        >>> print('Coordinate_zz_v:')
        M = 1
        lambda_c = 0.25
        chi_05 = 0
        zeta_c = 1
        Coordinate_zz_v = get_Coordinate_zz_v(
            M=M,
            lambda_c=lambda_c,
            chi_05=chi_05,
            zeta_c=zeta_c
        )
        print(f'M = {M}')
        print(f'lambda_c = {lambda_c}')
        print(f'chi_05 = {chi_05}')
        print(f'zeta_c = {zeta_c}')
        print('Result =', Coordinate_zz_v['Result'])
        print('x1_Min =', Coordinate_zz_v['x1']['Min'])
        print('x1_Value =', Coordinate_zz_v['x1']['Value'])
        print('x1_Max =', Coordinate_zz_v['x1']['Max'])
        print('x2_Min =', Coordinate_zz_v['x2']['Min'])
        print('x2_Value =', Coordinate_zz_v['x2']['Value'])
        print('x2_Max =', Coordinate_zz_v['x2']['Max'])
        print('x3_Min =', Coordinate_zz_v['x3']['Min'])
        print('x3_Value =', Coordinate_zz_v['x3']['Value'])
        print('x3_Max =', Coordinate_zz_v['x3']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_Coordinate_zz_v.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.c_float,
        ctypes.c_float,
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_Coordinate_zz_v.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}
    res_dict['x2'] = {}
    res_dict['x3'] = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x2 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x3 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_Coordinate_zz_v(
        ctypes.byref(Result),
        ctypes.c_float(M),
        ctypes.c_float(lambda_c),
        ctypes.c_float(chi_05),
        ctypes.c_float(zeta_c),
        ctypes.byref(x3),
        ctypes.byref(x2),
        ctypes.byref(x1),
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
        res_dict['x2']['Value'] = x2.Value
        res_dict['x2']['Min'] = x2.Min
        res_dict['x2']['Max'] = x2.Max
        res_dict['x3']['Value'] = x3.Value
        res_dict['x3']['Min'] = x3.Min
        res_dict['x3']['Max'] = x3.Max
    return res_dict


def get_interference_v(zeta_c, D, l, y_v, z_v):
    """Функция для определения коэффициента интерференции вихрей и задней несущей поверхности.

    Аргументы
    =========

        zeta_c: `float`
            Обратное сужение консолей (аргумент 1).  
        D: `float`
            Диаметр фюзеляжа, м (аргумент 2).
        l: `float`
            Размах несущей поверхности, м (аргумент 3).
        y_v: `float`
            Нормальная координата вихря, м (аргумент 4).
        z_v: `float`
            Поперечная координата вихря, м (аргумент 5).

    Выходные параметры
    ==================     

        'Result': `float`
            Коэффициент интерференции вихрей и задней несущей поверхности.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x2':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x3':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x4':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======
    
        >>> print('interference_v:')
        zeta_c = 1
        D = 1.2
        l = 2
        y_v = 0.4
        z_v = 1.7
        interference_v = get_interference_v(
            zeta_c=zeta_c,
            D=D,
            l=l,
            y_v=y_v,
            z_v=z_v
        )
        print(f'zeta_c = {zeta_c}')
        print(f'D = {D}')
        print(f'l = {l}')
        print(f'y_v = {y_v}')
        print(f'z_v = {z_v}')
        print('Result =', interference_v['Result'])
        print('x1_Min =', interference_v['x1']['Min'])
        print('x1_Value =', interference_v['x1']['Value'])
        print('x1_Max =', interference_v['x1']['Max'])
        print('x2_Min =', interference_v['x2']['Min'])
        print('x2_Value =', interference_v['x2']['Value'])
        print('x2_Max =', interference_v['x2']['Max'])
        print('x3_Min =', interference_v['x3']['Min'])
        print('x3_Value =', interference_v['x3']['Value'])
        print('x3_Max =', interference_v['x3']['Max'])
        print('x4_Min =', interference_v['x4']['Min'])
        print('x4_Value =', interference_v['x4']['Value'])
        print('x4_Max =', interference_v['x4']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_interference_v.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.c_float,
        ctypes.c_float,
        ctypes.c_float,
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_interference_v.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}
    res_dict['x2'] = {}
    res_dict['x3'] = {}
    res_dict['x4'] = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x2 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x3 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x4 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_interference_v(
        ctypes.byref(Result),
        ctypes.c_float(zeta_c),
        ctypes.c_float(D),
        ctypes.c_float(l),
        ctypes.c_float(y_v),
        ctypes.c_float(z_v),
        ctypes.byref(x4),
        ctypes.byref(x3),
        ctypes.byref(x2),
        ctypes.byref(x1),
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
        res_dict['x2']['Value'] = x2.Value
        res_dict['x2']['Min'] = x2.Min
        res_dict['x2']['Max'] = x2.Max
        res_dict['x3']['Value'] = x3.Value
        res_dict['x3']['Min'] = x3.Min
        res_dict['x3']['Max'] = x3.Max
        res_dict['x4']['Value'] = x4.Value
        res_dict['x4']['Min'] = x4.Min
        res_dict['x4']['Max'] = x4.Max
    return res_dict


def get_kM_Con(M, lambda_nos):
    """Функция для определения коэффициента\\
    торможения потока, вызванного обтеканием конической носовой части.

    Аргументы
    =========

        M: `float`
            Число Маха (аргумент 1).  
        lambda_nos: `float`
            Удлинение носовой части фюзеляжа (аргумент 2).

    Выходные параметры
    ==================     

        'Result': `float`
            Коэффициент торможения потока, вызванного обтеканием конической носовой части.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x2':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======

        >>> print('kM_Con:')
        M = 2
        lambda_nos = 1
        kM_Con = get_kM_Con(
            M=M,
            lambda_nos=lambda_nos
        )
        print(f'M = {M}')
        print(f'lambda_nos = {lambda_nos}')
        print('Result =', kM_Con['Result'])
        print('x1_Min =', kM_Con['x1']['Min'])
        print('x1_Value =', kM_Con['x1']['Value'])
        print('x1_Max =', kM_Con['x1']['Max'])
        print('x2_Min =', kM_Con['x2']['Min'])
        print('x2_Value =', kM_Con['x2']['Value'])
        print('x2_Max =', kM_Con['x2']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_kM_Con.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_kM_Con.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}
    res_dict['x2'] = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x2 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_kM_Con(
        ctypes.byref(Result),
        ctypes.c_float(M),
        ctypes.c_float(lambda_nos),
        ctypes.byref(x2),
        ctypes.byref(x1),
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
        res_dict['x2']['Value'] = x2.Value
        res_dict['x2']['Min'] = x2.Min
        res_dict['x2']['Max'] = x2.Max
    return res_dict


def get_kM_P(M, x, b_Ac):
    """Функция для определения коэффициента торможения потока,\\
    вызванного обтеканием передней несущей поверхности.

    Аргументы
    =========

        M: `float`
            Число Маха (аргумент 1).  
        x: `float`
            Расстояние между несущими поверхностями (аргумент 2).  
        b_Ac: `float`
            Средняя аэродинамическая хорда консолей передней несущей поверхности (аргумент 3).

    Выходные параметры
    ==================     

        'Result': `float`
            Коэффициент торможения потока, вызванного обтеканием передней несущей поверхности.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x2':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======

        >>> print('kM_P:')
        M = 1
        x = 1
        b_Ac = 1
        kM_P = get_kM_P(
            M=M,
            x=x,
            b_Ac=b_Ac
        )
        print(f'M = {M}')
        print(f'x = {x}')
        print(f'b_Ac = {b_Ac}')
        print('Result =', kM_P['Result'])
        print('x1_Min =', kM_P['x1']['Min'])
        print('x1_Value =', kM_P['x1']['Value'])
        print('x1_Max =', kM_P['x1']['Max'])
        print('x2_Min =', kM_P['x2']['Min'])
        print('x2_Value =', kM_P['x2']['Value'])
        print('x2_Max =', kM_P['x2']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_kM_P.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.c_float,
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_kM_P.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}
    res_dict['x2'] = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x2 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_kM_P(
        ctypes.byref(Result),
        ctypes.c_float(M),
        ctypes.c_float(x),
        ctypes.c_float(b_Ac),
        ctypes.byref(x2),
        ctypes.byref(x1),
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
        res_dict['x2']['Value'] = x2.Value
        res_dict['x2']['Min'] = x2.Min
        res_dict['x2']['Max'] = x2.Max
    return res_dict


def get_nn_Eff1(l_r, l_c, zeta_c):
    """Функция для определения коэффициента,\\
    характеризующего относительную эффективность концевых рулей.

    Аргументы
    =========

        l_r: `float`
            Размах рулей (аргумент 1).  
        l_c: `float`
            Расстояние между несущими поверхностями (аргумент 2).  
        zeta_c: `float`
            Сужение консолей (аргумент 3).

    Выходные параметры
    ==================     

        'Result': `float`
            Коэффициент, характеризующий относительную эффективность концевых рулей.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x2':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======

        >>> print('nn_Eff1:')
        l_r = 1
        l_c = 1
        zeta_c = 1
        nn_Eff1 = get_nn_Eff1(
            l_r=l_r,
            l_c=l_c,
            zeta_c=zeta_c
        )
        print(f'l_r = {l_r}')
        print(f'l_c = {l_c}')
        print(f'zeta_c = {zeta_c}')
        print('Result =', nn_Eff1['Result'])
        print('x1_Min =', nn_Eff1['x1']['Min'])
        print('x1_Value =', nn_Eff1['x1']['Value'])
        print('x1_Max =', nn_Eff1['x1']['Max'])
        print('x2_Min =', nn_Eff1['x2']['Min'])
        print('x2_Value =', nn_Eff1['x2']['Value'])
        print('x2_Max =', nn_Eff1['x2']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_nn_Eff1.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.c_float,
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_nn_Eff1.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}
    res_dict['x2'] = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x2 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_nn_Eff1(
        ctypes.byref(Result),
        ctypes.c_float(l_r),
        ctypes.c_float(l_c),
        ctypes.c_float(zeta_c),
        ctypes.byref(x2),
        ctypes.byref(x1),
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
        res_dict['x2']['Value'] = x2.Value
        res_dict['x2']['Min'] = x2.Min
        res_dict['x2']['Max'] = x2.Max
    return res_dict


def get_nn_Eff2(M, lambda_c, bb_r):
    """Функция для определения коэффициента,\\
    характеризующего относительную эффективность рулей,\\
    расположенных вдоль задней кромки.

    Аргументы
    =========

        M: `float`
            Число Маха (аргумент 1).  
        lambda_c: `float`
            Удлинение консолей несущей поверхности (аргумент 2).  
        bb_r: `float`
            Относительная хорда руля (аргумент 3).

    Выходные параметры
    ==================     

        'Result': `float`
            Коэффициент, характеризующий относительную\\
            эффективность рулей, расположенных вдоль задней кромки.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x2':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======

        >>> print('nn_Eff2:')
        M = 1
        lambda_c = 4
        bb_r = 0.05
        nn_Eff2 = get_nn_Eff2(
            M=M,
            lambda_c=lambda_c,
            bb_r=bb_r
        )
        print(f'M = {M}')
        print(f'lambda_c = {lambda_c}')
        print(f'bb_r = {bb_r}')
        print('Result =', nn_Eff2['Result'])
        print('x1_Min =', nn_Eff2['x1']['Min'])
        print('x1_Value =', nn_Eff2['x1']['Value'])
        print('x1_Max =', nn_Eff2['x1']['Max'])
        print('x2_Min =', nn_Eff2['x2']['Min'])
        print('x2_Value =', nn_Eff2['x2']['Value'])
        print('x2_Max =', nn_Eff2['x2']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_nn_Eff2.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.c_float,
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_nn_Eff2.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}
    res_dict['x2'] = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x2 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_nn_Eff2(
        ctypes.byref(Result),
        ctypes.c_float(M),
        ctypes.c_float(lambda_c),
        ctypes.c_float(bb_r),
        ctypes.byref(x2),
        ctypes.byref(x1),
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
        res_dict['x2']['Value'] = x2.Value
        res_dict['x2']['Min'] = x2.Min
        res_dict['x2']['Max'] = x2.Max
    return res_dict


def get_Cp1_Cp2(M, key):
    """Функция для определения коэффициентов,\\
    определяющих давление на поверхности профиля\\
    по теории 2-ого приближения.

    Аргументы
    =========

        M: `float`
            Число Маха (аргумент 1). 
        key: `float`
            Ключ, определяющий коэффициент,\\
            который возвращает функция (аргумент 2):\\
                key = 1 - первый коэффициент;\\
                key = 2 - второй коэффициент;\\
                key = 0 - отношение второго коэффициента к первому коэффициенту.

    Выходные параметры
    ==================     

        'Result': `float`
            Коэффициенты, определяющие давление на\\
            поверхности профиля по теории 2-ого приближения.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======

        >>> print('Cp1_Cp2:')
        M = 1.8
        key = 0
        Cp1_Cp2 = get_Cp1_Cp2(
            M=M,
            key=key
        )
        print(f'M = {M}')
        print(f'key = {key}')
        print('Result =', Cp1_Cp2['Result'])
        print('x1_Min =', Cp1_Cp2['x1']['Min'])
        print('x1_Value =', Cp1_Cp2['x1']['Value'])
        print('x1_Max =', Cp1_Cp2['x1']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_Cp1_Cp2.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_Cp1_Cp2.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_Cp1_Cp2(
        ctypes.byref(Result),
        ctypes.c_float(M),
        ctypes.c_float(key),
        ctypes.byref(x1),
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
    return res_dict


def get_Cx_Cil_N(M, alpha):
    """Функция для определения среднего по длине\\
    цилиндра коэффициента сопротивления при обтекании\\
    цилиндра по нормали к его оси.

    Аргументы
    =========

        M: `float`
            Число Маха (аргумент 1). 
        alpha: `float`
            Угол атаки, рад (аргумент 2).

    Выходные параметры
    ==================     

        'Result': `float`
            Средний по длине цилиндра коэффициент сопротивления\\
            при обтекании цилиндра по нормали к его оси.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======

        >>> print('Cx_Cil_N:')
        M = 0.8
        alpha = 1.57
        Cx_Cil_N = get_Cx_Cil_N(
            M=M,
            alpha=alpha
        )
        print(f'M = {M}')
        print(f'alpha = {alpha}')
        print('Result =', Cx_Cil_N['Result'])
        print('x1_Min =', Cx_Cil_N['x1']['Min'])
        print('x1_Value =', Cx_Cil_N['x1']['Value'])
        print('x1_Max =', Cx_Cil_N['x1']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_Cx_Cil_N.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_Cx_Cil_N.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_Cx_Cil_N(
        ctypes.byref(Result),
        ctypes.c_float(M),
        ctypes.c_float(alpha),
        ctypes.byref(x1),
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
    return res_dict


def get_A_IsP(M, zeta_c, Cyalf_IsP):
    """Функция для определения коэффициента дополнительной\\
    нормальной силы несущей поверхности при больших углах атаки.

    Аргументы
    =========

        M: `float`
            Число Маха (аргумент 1).  
        zeta_c: `float`
            Сужение консолей (аргумент 2).
        Cyalf_IsP: `float`
            Производная по углу атаки коэффициента\\
            подъёмной силы изолированной несущей поверхности,\\
            1/рад (аргумент 3).

    Выходные параметры
    ==================     

        'Result': `float`
            Коэффициент дополнительной нормальной силы\\
            несущей поверхности при больших углах атаки.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x2':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x3':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======

        >>> print('A_IsP:')
        M = 2
        zeta_c = 1
        Cyalf_IsP = np.rad2deg(0.03)
        A_IsP = get_A_IsP(
            M=M,
            zeta_c=zeta_c,
            Cyalf_IsP=Cyalf_IsP
        )
        print(f'M = {M}')
        print(f'zeta_c = {zeta_c}')
        print(f'Cyalf_IsP = {Cyalf_IsP}')
        print('Result =', A_IsP['Result'])
        print('x1_Min =', A_IsP['x1']['Min'])
        print('x1_Value =', A_IsP['x1']['Value'])
        print('x1_Max =', A_IsP['x1']['Max'])
        print('x2_Min =', A_IsP['x2']['Min'])
        print('x2_Value =', A_IsP['x2']['Value'])
        print('x2_Max =', A_IsP['x2']['Max'])
        print('x3_Min =', A_IsP['x3']['Min'])
        print('x3_Value =', A_IsP['x3']['Value'])
        print('x3_Max =', A_IsP['x3']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_A_IsP.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.c_float,
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_A_IsP.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}
    res_dict['x2'] = {}
    res_dict['x3'] = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x2 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x3 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_A_IsP(
        ctypes.byref(Result),
        ctypes.c_float(M),
        ctypes.c_float(zeta_c),
        ctypes.c_float(Cyalf_IsP),
        ctypes.byref(x3),
        ctypes.byref(x2),
        ctypes.byref(x1),
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
        res_dict['x2']['Value'] = x2.Value
        res_dict['x2']['Min'] = x2.Min
        res_dict['x2']['Max'] = x2.Max
        res_dict['x3']['Value'] = x3.Value
        res_dict['x3']['Min'] = x3.Min
        res_dict['x3']['Max'] = x3.Max
    return res_dict


def get_Cf_M0(Re, xx_t):
    """Функция для определения коэффициента трения плоской пластинки при М = 0.

    Аргументы
    =========

        Re: `float`
            Число Рейнольдса (аргумент 1).  
        xx_t: `float`
            Относительная координата точки перехода\\
            ламинарного пограничного слоя в турбулентный (аргумент 2).

    Выходные параметры
    ==================     

        'Result': `float`
            Коэффициент трения плоской пластинки при М = 0.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x2':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======

        >>> print('Cf_M0:')
        Re = 1e6
        xx_t = 1
        Cf_M0 = get_Cf_M0(
            Re = Re,
            xx_t = xx_t
        )
        print(f'Re = {Re}')
        print(f'xx_t = {xx_t}')
        print('Result =', 2*Cf_M0['Result'])
        print('x1_Min =', Cf_M0['x1']['Min'])
        print('x1_Value =', Cf_M0['x1']['Value'])
        print('x1_Max =', Cf_M0['x1']['Max'])
        print('x2_Min =', Cf_M0['x2']['Min'])
        print('x2_Value =', Cf_M0['x2']['Value'])
        print('x2_Max =', Cf_M0['x2']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_Cf_M0.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_Cf_M0.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}
    res_dict['x2'] = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x2 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_Cf_M0(
        ctypes.byref(Result),
        ctypes.c_float(Re),
        ctypes.c_float(xx_t),
        ctypes.byref(x2),
        ctypes.byref(x1),
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
        res_dict['x2']['Value'] = x2.Value
        res_dict['x2']['Min'] = x2.Min
        res_dict['x2']['Max'] = x2.Max
    return res_dict


def get_Sigma_M(M, xx_t):
    """Функция для определения поправочного множителя, учитывающего\\
    влияние числа Маха на коэффициент трения плоской пластинки.

    Аргументы
    =========

        M: `float`
            Число Маха (аргумент 1).  
        xx_t: `float`
            Относительная координата точки перехода\\
            ламинарного пограничного слоя в турбулентный (аргумент 2).

    Выходные параметры
    ==================     

        'Result': `float`
            Поправочный множитель, учитывающий влияние числа Маха\\
            на коэффициент трения плоской пластинки.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x2':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======

        >>> print('Sigma_M:')
        M = 4
        xx_t = 1
        Sigma_M = get_Sigma_M(
            M=M,
            xx_t=xx_t
        )
        print(f'M = {M}')
        print(f'xx_t = {xx_t}')
        print('Result =', Sigma_M['Result'])
        print('x1_Min =', Sigma_M['x1']['Min'])
        print('x1_Value =', Sigma_M['x1']['Value'])
        print('x1_Max =', Sigma_M['x1']['Max'])
        print('x2_Min =', Sigma_M['x2']['Min'])
        print('x2_Value =', Sigma_M['x2']['Value'])
        print('x2_Max =', Sigma_M['x2']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_Sigma_M.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_Sigma_M.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}
    res_dict['x2'] = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x2 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_Sigma_M(
        ctypes.byref(Result),
        ctypes.c_float(M),
        ctypes.c_float(xx_t),
        ctypes.byref(x2),
        ctypes.byref(x1),
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
        res_dict['x2']['Value'] = x2.Value
        res_dict['x2']['Min'] = x2.Min
        res_dict['x2']['Max'] = x2.Max
    return res_dict


def get_Re_t0_1(M, Re, hh):
    """Функция для определения критического числа Рейнольдса\\
    при шероховатой поверхности тела, отсутствии теплопередачи\\
    и нулевом градиенте давления.

    Аргументы
    =========

        M: `float`
            Число Маха (аргумент 1).  
        Re: `float`
            Число Рейнольдса (аргумент 2). 
        hh: `float`
            Относительная высота бугорков шероховатости\\
            поверхности (аргумент 3).

    Выходные параметры
    ==================     

        'Result': `float`
            Критическое число Рейнольдса при отсутствии\\
            теплопередачи и нулевом градиенте давления.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x2':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======

        >>> print('Re_t0_1:')
        M = 1
        Re = 10
        hh = 0
        Re_t0_1 = get_Re_t0_1(
            M=M,
            Re=Re,
            hh=hh
        )
        print(f'M = {M}')
        print(f'Re = {Re}')
        print(f'hh = {hh}')
        print('Result =', Re_t0_1['Result'])
        print('x1_Min =', Re_t0_1['x1']['Min'])
        print('x1_Value =', Re_t0_1['x1']['Value'])
        print('x1_Max =', Re_t0_1['x1']['Max'])
        print('x2_Min =', Re_t0_1['x2']['Min'])
        print('x2_Value =', Re_t0_1['x2']['Value'])
        print('x2_Max =', Re_t0_1['x2']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_Re_t0_1.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.c_float,
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_Re_t0_1.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}
    res_dict['x2'] = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x2 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_Re_t0_1(
        ctypes.byref(Result),
        ctypes.c_float(M),
        ctypes.c_float(Re),
        ctypes.c_float(hh),
        ctypes.byref(x2),
        ctypes.byref(x1),
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
        res_dict['x2']['Value'] = x2.Value
        res_dict['x2']['Min'] = x2.Min
        res_dict['x2']['Max'] = x2.Max
    return res_dict


def get_TTr_TTsl(M, key):
    """Функция для определения относительной температуры восстановления\\
    и относительной температуры поверхности гладкой стенки, при которой\\
    ламинарный пограничный слой является устойчивым.

    Аргументы
    =========

        M: `float`
            Число Маха (аргумент 1).  
        key: `float`
            Ключ, определяющий относительную температуру,\\
            которую возвращает функция (аргумент 2):
                key = 1 - T_r/T;\\
                key = 2 - T_ст^л/T;\\
                key = 0 - T_ст^л/T_r.

    Выходные параметры
    ==================     

        'Result': `float`
            Температуры восстановления к температуре окружающей среды\\
            или отношение температуры поверхности тела, при которой ламинарный\\
            пограничный слой является устойчивым, к температуре окружающей среды.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======

        >>> print('TTr_TTsl:')
        M = 1
        key = 2
        TTr_TTsl = get_TTr_TTsl(
            M=M,
            key=key
        )
        print(f'M = {M}')
        print(f'key = {key}')
        print('Result =', TTr_TTsl['Result'])
        print('x1_Min =', TTr_TTsl['x1']['Min'])
        print('x1_Value =', TTr_TTsl['x1']['Value'])
        print('x1_Max =', TTr_TTsl['x1']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_TTr_TTsl.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_TTr_TTsl.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_TTr_TTsl(
        ctypes.byref(Result),
        ctypes.c_float(M),
        ctypes.c_float(key),
        ctypes.byref(x1),
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
    return res_dict


def get_Sigma_T(M, TT_s):
    """Функция для определения поправочного множителя, учитывающего\\
    влияние температуры поверхности тела на критическое число Рейнольдса.

    Аргументы
    =========

        M: `float`
            Число Маха (аргумент 1).  
        TT_s: `float`
            Относительная температура поверхности тела (аргумент 2).

    Выходные параметры
    ==================     

        'Result': `float`
            Поправочный множитель, учитывающий влияние температуры\\
            поверхности тела на критическое число Рейнольдса.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======

        >>> print('Sigma_T:')
        M = 3.12
        TT_s = 0.6
        Sigma_T = get_Sigma_T(
            M=M,
            TT_s=TT_s
        )
        print(f'M = {M}')
        print(f'TT_s = {TT_s}')
        print('Result =', Sigma_T['Result'])
        print('x1_Min =', Sigma_T['x1']['Min'])
        print('x1_Value =', Sigma_T['x1']['Value'])
        print('x1_Max =', Sigma_T['x1']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_Sigma_T.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_Sigma_T.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_Sigma_T(
        ctypes.byref(Result),
        ctypes.c_float(M),
        ctypes.c_float(TT_s),
        ctypes.byref(x1),
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
    return res_dict


def get_Sigma_Con(M, lambda_nos):
    """Функция для определения поправочного множителя, учитывающего отличие\\
    коэффициента трения конуса от коэффициента трения плоской пластинки.

    Аргументы
    =========

        M: `float`
            Число Маха (аргумент 1).  
        lambda_nos: `float`
            Удлинение носовой части фюзеляжа (аргумент 2). 

    Выходные параметры
    ==================     

        'Result': `float`
            Поправочный множитель, учитывающий отличие коэффициента\\
            трения конуса от коэффициента трения плоской пластинки.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x2':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======

        >>> print('Sigma_Con:')
        M = 10
        lambda_nos = 5
        Sigma_Con = get_Sigma_Con(
            M=M,
            lambda_nos=lambda_nos
        )
        print(f'M = {M}')
        print(f'lambda_nos = {lambda_nos}')
        print('Result =', Sigma_Con['Result'])
        print('x1_Min =', Sigma_Con['x1']['Min'])
        print('x1_Value =', Sigma_Con['x1']['Value'])
        print('x1_Max =', Sigma_Con['x1']['Max'])
        print('x2_Min =', Sigma_Con['x2']['Min'])
        print('x2_Value =', Sigma_Con['x2']['Value'])
        print('x2_Max =', Sigma_Con['x2']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_Sigma_Con.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_Sigma_Con.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}
    res_dict['x2'] = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x2 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_Sigma_Con(
        ctypes.byref(Result),
        ctypes.c_float(M),
        ctypes.c_float(lambda_nos),
        ctypes.byref(x2),
        ctypes.byref(x1),
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
        res_dict['x2']['Value'] = x2.Value
        res_dict['x2']['Min'] = x2.Min
        res_dict['x2']['Max'] = x2.Max
    return res_dict


def get_Cxnos_Con(M, lambda_nos):
    """Функция для определения коэффициента сопротивления давления конической носовой части.

    Аргументы
    =========

        M: `float`
            Число Маха (аргумент 1).  
        lambda_nos: `float`
            Удлинение носовой части фюзеляжа (аргумент 2). 

    Выходные параметры
    ==================     

        'Result': `float`
            Сопротивление давления конической носовой части.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x2':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======

        >>> print('Cxnos_Con:')
        M = 1.4
        lambda_nos = 1.5
        Cxnos_Con = get_Cxnos_Con(
            M=M,
            lambda_nos=lambda_nos
        )
        print(f'M = {M}')
        print(f'lambda_nos = {lambda_nos}')
        print('Result =', Cxnos_Con['Result'])
        print('x1_Min =', Cxnos_Con['x1']['Min'])
        print('x1_Value =', Cxnos_Con['x1']['Value'])
        print('x1_Max =', Cxnos_Con['x1']['Max'])
        print('x2_Min =', Cxnos_Con['x2']['Min'])
        print('x2_Value =', Cxnos_Con['x2']['Value'])
        print('x2_Max =', Cxnos_Con['x2']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_Cxnos_Con.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_Cxnos_Con.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}
    res_dict['x2'] = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x2 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_Cxnos_Con(
        ctypes.byref(Result),
        ctypes.c_float(M),
        ctypes.c_float(lambda_nos),
        ctypes.byref(x2),
        ctypes.byref(x1),
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
        res_dict['x2']['Value'] = x2.Value
        res_dict['x2']['Min'] = x2.Min
        res_dict['x2']['Max'] = x2.Max
    return res_dict


def get_Cxnos_Par(M, lambda_nos):
    """Функция для определения коэффициента сопротивления давления параболической носовой части.

    Аргументы
    =========

        M: `float`
            Число Маха (аргумент 1).  
        lambda_nos: `float`
            Удлинение носовой части фюзеляжа (аргумент 2). 

    Выходные параметры
    ==================     

        'Result': `float`
            Сопротивление давления параболической носовой части.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x2':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======

        >>> print('Cxnos_Par:')
        M = 1.4
        lambda_nos = 2
        Cxnos_Par = get_Cxnos_Par(
            M=M,
            lambda_nos=lambda_nos
        )
        print(f'M = {M}')
        print(f'lambda_nos = {lambda_nos}')
        print('Result =', Cxnos_Par['Result'])
        print('x1_Min =', Cxnos_Par['x1']['Min'])
        print('x1_Value =', Cxnos_Par['x1']['Value'])
        print('x1_Max =', Cxnos_Par['x1']['Max'])
        print('x2_Min =', Cxnos_Par['x2']['Min'])
        print('x2_Value =', Cxnos_Par['x2']['Value'])
        print('x2_Max =', Cxnos_Par['x2']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_Cxnos_Par.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_Cxnos_Par.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}
    res_dict['x2'] = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x2 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_Cxnos_Par(
        ctypes.byref(Result),
        ctypes.c_float(M),
        ctypes.c_float(lambda_nos),
        ctypes.byref(x2),
        ctypes.byref(x1),
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
        res_dict['x2']['Value'] = x2.Value
        res_dict['x2']['Min'] = x2.Min
        res_dict['x2']['Max'] = x2.Max
    return res_dict


def get_Cxnos_Ell(M, lambda_nos):
    """Функция для определения коэффициента сопротивления давления эллиптической носовой части.

    Аргументы
    =========

        M: `float`
            Число Маха (аргумент 1).  
        lambda_nos: `float`
            Удлинение носовой части фюзеляжа (аргумент 2). 

    Выходные параметры
    ==================     

        'Result': `float`
            Сопротивление давления эллиптической носовой части.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x2':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======

        >>> print('Cxnos_Ell:')
        M = 1.4
        lambda_nos = 0
        Cxnos_Ell = get_Cxnos_Ell(
            M=M,
            lambda_nos=lambda_nos
        )
        print(f'M = {M}')
        print(f'lambda_nos = {lambda_nos}')
        print('Result =', Cxnos_Ell['Result'])
        print('x1_Min =', Cxnos_Ell['x1']['Min'])
        print('x1_Value =', Cxnos_Ell['x1']['Value'])
        print('x1_Max =', Cxnos_Ell['x1']['Max'])
        print('x2_Min =', Cxnos_Ell['x2']['Min'])
        print('x2_Value =', Cxnos_Ell['x2']['Value'])
        print('x2_Max =', Cxnos_Ell['x2']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_Cxnos_Ell.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_Cxnos_Ell.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}
    res_dict['x2'] = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x2 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_Cxnos_Ell(
        ctypes.byref(Result),
        ctypes.c_float(M),
        ctypes.c_float(lambda_nos),
        ctypes.byref(x2),
        ctypes.byref(x1),
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
        res_dict['x2']['Value'] = x2.Value
        res_dict['x2']['Min'] = x2.Min
        res_dict['x2']['Max'] = x2.Max
    return res_dict


def get_Ms_Con(M, teta_Con):
    """Функция для определения числа Маха на поверхности конуса.

    Аргументы
    =========

        M: `float`
            Число Маха (аргумент 1).  
        teta_Con: `float`
            Полуугол при вершине конуса, рад (аргумент 2). 

    Выходные параметры
    ==================     

        'Result': `float`
            Число Маха на поверхности стенки конуса.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x2':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======

        >>> print('Ms_Con:')
        M = 7
        teta_Con = 0.35
        Ms_Con = get_Ms_Con(
            M=M,
            teta_Con=teta_Con
        )
        print(f'M = {M}')
        print(f'teta_Con = {teta_Con}')
        print('Result =', Ms_Con['Result'])
        print('x1_Min =', Ms_Con['x1']['Min'])
        print('x1_Value =', Ms_Con['x1']['Value'])
        print('x1_Max =', Ms_Con['x1']['Max'])
        print('x2_Min =', Ms_Con['x2']['Min'])
        print('x2_Value =', Ms_Con['x2']['Value'])
        print('x2_Max =', Ms_Con['x2']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_Ms_Con.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_Ms_Con.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}
    res_dict['x2'] = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x2 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_Ms_Con(
        ctypes.byref(Result),
        ctypes.c_float(M),
        ctypes.c_float(teta_Con),
        ctypes.byref(x2),
        ctypes.byref(x1),
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
        res_dict['x2']['Value'] = x2.Value
        res_dict['x2']['Min'] = x2.Min
        res_dict['x2']['Max'] = x2.Max
    return res_dict


def get_Cxcor_Con(M, lambda_cor, eta_cor):
    """Функция для определения коэффициента сопротивления давления конической кормовой части.

    Аргументы
    =========

        M: `float`
            Число Маха (аргумент 1).  
        lambda_cor: `float`
            Удлинение кормовой части фюзеляжа (аргумент 2).
        eta_cor: `float`
            Сужение кормовой части фюзеляжа (аргумент 3).

    Выходные параметры
    ==================     

        'Result': `float`
            Коэффициент сопротивления давления конической кормовой части корпуса.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x2':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x3':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======

        >>> print('Cxcor_Con:')
        M = 4.5
        lambda_cor = 1.5
        eta_cor = 0.5
        Cxcor_Con = get_Cxcor_Con(
            M=M,
            lambda_cor=lambda_cor,
            eta_cor=eta_cor
        )
        print(f'M = {M}')
        print(f'lambda_cor = {lambda_cor}')
        print(f'eta_cor = {eta_cor}')
        print('Result =', Cxcor_Con['Result'])
        print('x1_Min =', Cxcor_Con['x1']['Min'])
        print('x1_Value =', Cxcor_Con['x1']['Value'])
        print('x1_Max =', Cxcor_Con['x1']['Max'])
        print('x2_Min =', Cxcor_Con['x2']['Min'])
        print('x2_Value =', Cxcor_Con['x2']['Value'])
        print('x2_Max =', Cxcor_Con['x2']['Max'])
        print('x3_Min =', Cxcor_Con['x3']['Min'])
        print('x3_Value =', Cxcor_Con['x3']['Value'])
        print('x3_Max =', Cxcor_Con['x3']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_Cxcor_Con.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.c_float,
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_Cxcor_Con.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}
    res_dict['x2'] = {}
    res_dict['x3'] = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x2 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x3 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_Cxcor_Con(
        ctypes.byref(Result),
        ctypes.c_float(M),
        ctypes.c_float(lambda_cor),
        ctypes.c_float(eta_cor),
        ctypes.byref(x3),
        ctypes.byref(x2),
        ctypes.byref(x1),
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
        res_dict['x2']['Value'] = x2.Value
        res_dict['x2']['Min'] = x2.Min
        res_dict['x2']['Max'] = x2.Max
        res_dict['x3']['Value'] = x3.Value
        res_dict['x3']['Min'] = x3.Min
        res_dict['x3']['Max'] = x3.Max
    return res_dict


def get_Cxcor_Par(M, lambda_cor, eta_cor):
    """Функция для определения коэффициента сопротивления давления параболической кормовой части.

    Аргументы
    =========

        M: `float`
            Число Маха (аргумент 1).  
        lambda_cor: `float`
            Удлинение кормовой части фюзеляжа (аргумент 2).
        eta_cor: `float`
            Сужение кормовой части фюзеляжа (аргумент 3).

    Выходные параметры
    ==================     

        'Result': `float`
            Коэффициент сопротивления давления параболической кормовой части корпуса.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x2':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x3':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======

        >>> print('Cxcor_Par:')
        M = 1.4
        lambda_cor = 3
        eta_cor = 0
        Cxcor_Par = get_Cxcor_Par(
            M=M,
            lambda_cor=lambda_cor,
            eta_cor=eta_cor
        )
        print(f'M = {M}')
        print(f'lambda_cor = {lambda_cor}')
        print(f'eta_cor = {eta_cor}')
        print('Result =', Cxcor_Par['Result'])
        print('x1_Min =', Cxcor_Par['x1']['Min'])
        print('x1_Value =', Cxcor_Par['x1']['Value'])
        print('x1_Max =', Cxcor_Par['x1']['Max'])
        print('x2_Min =', Cxcor_Par['x2']['Min'])
        print('x2_Value =', Cxcor_Par['x2']['Value'])
        print('x2_Max =', Cxcor_Par['x2']['Max'])
        print('x3_Min =', Cxcor_Par['x3']['Min'])
        print('x3_Value =', Cxcor_Par['x3']['Value'])
        print('x3_Max =', Cxcor_Par['x3']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_Cxcor_Par.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.c_float,
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_Cxcor_Par.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}
    res_dict['x2'] = {}
    res_dict['x3'] = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x2 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x3 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_Cxcor_Par(
        ctypes.byref(Result),
        ctypes.c_float(M),
        ctypes.c_float(lambda_cor),
        ctypes.c_float(eta_cor),
        ctypes.byref(x3),
        ctypes.byref(x2),
        ctypes.byref(x1),
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
        res_dict['x2']['Value'] = x2.Value
        res_dict['x2']['Min'] = x2.Min
        res_dict['x2']['Max'] = x2.Max
        res_dict['x3']['Value'] = x3.Value
        res_dict['x3']['Min'] = x3.Min
        res_dict['x3']['Max'] = x3.Max
    return res_dict


def get_Cxdon_Cil(M, cc, Re_f06, Re_f, xx_tf, lambda_f):
    """Функция для определения коэффициента донного сопротивления фюзеляжа с цилиндрической кормовой частью.

    Аргументы
    =========

        M: `float`
            Число Маха (аргумент 1).  
        cc: `float`
            Относительная толщина профиля задней несущей поверхности (аргумент 2). 
        Re_f06: `float`
            Число Рейнольдса для фюзеляжа при скорости, соответствующей М = 0.6 (аргумент 3). 
        Re_f: `float`
            Число Рейнольдса для фюзеляжа при скорости, соответствующей М (аргумент 4). 
        xx_tf: `float`
            Относительная координата точки перехода ламинарного пограничного слоя в турбулентный на фюзеляже (аргумент 5). 
        lambda_f: `float`
            Удлинение фюзеляжа (аргумент 6). 

    Выходные параметры
    ==================     

        'Result': `float`
            Коэффициент донного сопротивления фюзеляжа с цилиндрической кормовой частью.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x2':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======

        >>> print('Cxdon_Cil:')
        a, L_f, nu = 320.545, 1, 22.11e-6
        def Re(M): return M * a * L_f / nu
        M = 0.8
        cc = 0
        Re_f06 = Re(0.6)
        Re_f = Re(0.8)
        xx_tf = 0.2
        lambda_f = 4
        Cxdon_Cil = get_Cxdon_Cil(
            M=M,
            cc=cc,
            Re_f06=Re_f06,
            Re_f=Re_f,
            xx_tf=xx_tf,
            lambda_f=lambda_f
        )
        print(f'M = {M}')
        print(f'cc = {cc}')
        print(f'Re_f06 = {Re_f06}')
        print(f'Re_f = {Re_f}')
        print(f'xx_tf = {xx_tf}')
        print(f'lambda_f = {lambda_f}')
        print('Result =', Cxdon_Cil['Result'])
        print('x1_Min =', Cxdon_Cil['x1']['Min'])
        print('x1_Value =', Cxdon_Cil['x1']['Value'])
        print('x1_Max =', Cxdon_Cil['x1']['Max'])
        print('x2_Min =', Cxdon_Cil['x2']['Min'])
        print('x2_Value =', Cxdon_Cil['x2']['Value'])
        print('x2_Max =', Cxdon_Cil['x2']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_Cxdon_Cil.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.c_float,
        ctypes.c_float,
        ctypes.c_float,
        ctypes.c_float,
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_Cxdon_Cil.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}
    res_dict['x2'] = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x2 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_Cxdon_Cil(
        ctypes.byref(Result),
        ctypes.c_float(M),
        ctypes.c_float(cc),
        ctypes.c_float(Re_f06),
        ctypes.c_float(Re_f),
        ctypes.c_float(xx_tf),
        ctypes.c_float(lambda_f),
        ctypes.byref(x2),
        ctypes.byref(x1),
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
        res_dict['x2']['Value'] = x2.Value
        res_dict['x2']['Min'] = x2.Min
        res_dict['x2']['Max'] = x2.Max
    return res_dict


def get_Sigma_eta(M, lambda_cor, eta_cor):
    """Функция для определения поправочного множителя, учитывающего влияние сужающейся\\
    кормовой части на коэффициент донного сопротивления фюзеляжа.

    Аргументы
    =========

        M: `float`
            Число Маха (аргумент 1).  
        lambda_cor: `float`
            Удлинение кормовой части фюзеляжа (аргумент 2). 
        eta_cor: `float`
            Сужение кормовой части фюзеляжа (аргумент 3). 

    Выходные параметры
    ==================     

        'Result': `float`
            Поправочный множитель, учитывающий влияние сужающейся кормовой части на коэффициент донного сопротивления фюзеляжа.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x2':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======

        >>> print('Sigma_eta:')
        M = 1.5
        lambda_cor = 1
        eta_cor = 1
        Sigma_eta = get_Sigma_eta(
            M=M,
            lambda_cor=lambda_cor,
            eta_cor=eta_cor
        )
        print(f'M = {M}')
        print(f'lambda_cor = {lambda_cor}')
        print(f'eta_cor = {eta_cor}')
        print('Result =', Sigma_eta['Result'])
        print('x1_Min =', Sigma_eta['x1']['Min'])
        print('x1_Value =', Sigma_eta['x1']['Value'])
        print('x1_Max =', Sigma_eta['x1']['Max'])
        print('x2_Min =', Sigma_eta['x2']['Min'])
        print('x2_Value =', Sigma_eta['x2']['Value'])
        print('x2_Max =', Sigma_eta['x2']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_Sigma_eta.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.c_float,
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_Sigma_eta.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}
    res_dict['x2'] = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x2 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_Sigma_eta(
        ctypes.byref(Result),
        ctypes.c_float(M),
        ctypes.c_float(lambda_cor),
        ctypes.c_float(eta_cor),
        ctypes.byref(x2),
        ctypes.byref(x1),
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
        res_dict['x2']['Value'] = x2.Value
        res_dict['x2']['Min'] = x2.Min
        res_dict['x2']['Max'] = x2.Max
    return res_dict


def get_Sigma_c(cc, xx_t):
    """Функция для определения поправочного множителя, учитывающего влияние толщины\\
    профиля на коэффициент профильного сопротивления несущей поверхности.

    Аргументы
    =========

        cc: `float`
            Относительная толщина профиля (аргумент 1).  
        xx_t: `float`
            Относительная координата точки перехода ламинарного пограничного слоя в турбулентный (аргумент 2). 

    Выходные параметры
    ==================     

        'Result': `float`
            Поправочный множитель, учитывающий влияние толщины профиля на коэффициент профильного сопротивления несущей поверхности.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x2':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======

        >>> print('Sigma_c:')
        cc = 0.1
        xx_t = 0.4
        Sigma_c = get_Sigma_c(
            cc=cc,
            xx_t=xx_t
        )
        print(f'cc = {cc}')
        print(f'xx_t = {xx_t}')
        print('Result =', Sigma_c['Result'])
        print('x1_Min =', Sigma_c['x1']['Min'])
        print('x1_Value =', Sigma_c['x1']['Value'])
        print('x1_Max =', Sigma_c['x1']['Max'])
        print('x2_Min =', Sigma_c['x2']['Min'])
        print('x2_Value =', Sigma_c['x2']['Value'])
        print('x2_Max =', Sigma_c['x2']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_Sigma_c.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_Sigma_c.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}
    res_dict['x2'] = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x2 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_Sigma_c(
        ctypes.byref(Result),
        ctypes.c_float(cc),
        ctypes.c_float(xx_t),
        ctypes.byref(x2),
        ctypes.byref(x1),
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
        res_dict['x2']['Value'] = x2.Value
        res_dict['x2']['Min'] = x2.Min
        res_dict['x2']['Max'] = x2.Max
    return res_dict


def get_Sigma_chi(chi_0):
    """Функция для определения поправочного множителя, учитывающего влияние угла\\
    стреловидности по передней кромке на критическое число Рейнольдса.

    Аргументы
    =========

        chi_0: `float`
            Угол стреловидности по передней кромке несущей поверхности, рад (аргумент 1).  

    Выходные параметры
    ==================     

        'Result': `float`
            Поправочный множитель, учитывающий влияние угла стреловидности по передней кромке на критическое число Рейнольдса.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======

        >>> print('Sigma_chi:')
        chi_0 = 1.05
        Sigma_chi = get_Sigma_chi(
            chi_0=chi_0
        )
        print(f'chi_0 = {chi_0}')
        print('Result =', Sigma_chi['Result'])
        print('x1_Min =', Sigma_chi['x1']['Min'])
        print('x1_Value =', Sigma_chi['x1']['Value'])
        print('x1_Max =', Sigma_chi['x1']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_Sigma_chi.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_Sigma_chi.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_Sigma_chi(
        ctypes.byref(Result),
        ctypes.c_float(chi_0),
        ctypes.byref(x1),
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
    return res_dict


def get_Cxw_Rhomb_M1(M, cc, zeta_c, chi_c, lambda_c):
    """Функция для определения коэффициента волнового сопротивления несущей поверхности с ромбовидным профилем при M ≥ 1.

    Аргументы
    =========

        M: `float`
            Число Маха (аргумент 1).  
        cc: `float`
            Относительная толщина профиля (аргумент 2).
        zeta_c: `float`
            Обратное сужение консолей (аргумент 3).
        chi_c: `float`
            Угол стреловидности по линии\\
            максимальных толщин, рад (аргумент 4).
        lambda_c: `float`
            Удлинение консолей несущей поверхности (аргумент 5).

    Выходные параметры
    ==================     

        'Result': `float`
            Коэффициент волнового сопротивления несущей\\
            поверхности с ромбовидным профилем при M ≥ 1.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x2':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x3':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x4':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======

        >>> print('Cxw_Rhomb_M1:')
        M = 1
        cc = 1
        zeta_c = 1
        chi_c = 0
        lambda_c = 1
        Cxw_Rhomb_M1 = get_Cxw_Rhomb_M1(
            M=M,
            cc=cc,
            zeta_c=zeta_c,
            chi_c=chi_c,
            lambda_c=lambda_c
        )
        print(f'M = {M}')
        print(f'cc = {cc}')
        print(f'zeta_c = {zeta_c}')
        print(f'chi_c = {chi_c}')
        print(f'lambda_c = {lambda_c}')
        print('Result =', Cxw_Rhomb_M1['Result'] / lambda_c / cc**2)
        print('x1_Min =', Cxw_Rhomb_M1['x1']['Min'])
        print('x1_Value =', Cxw_Rhomb_M1['x1']['Value'])
        print('x1_Max =', Cxw_Rhomb_M1['x1']['Max'])
        print('x2_Min =', Cxw_Rhomb_M1['x2']['Min'])
        print('x2_Value =', Cxw_Rhomb_M1['x2']['Value'])
        print('x2_Max =', Cxw_Rhomb_M1['x2']['Max'])
        print('x3_Min =', Cxw_Rhomb_M1['x3']['Min'])
        print('x3_Value =', Cxw_Rhomb_M1['x3']['Value'])
        print('x3_Max =', Cxw_Rhomb_M1['x3']['Max'])
        print('x4_Min =', Cxw_Rhomb_M1['x4']['Min'])
        print('x4_Value =', Cxw_Rhomb_M1['x4']['Value'])
        print('x4_Max =', Cxw_Rhomb_M1['x4']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_Cxw_Rhomb_M1.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.c_float,
        ctypes.c_float,
        ctypes.c_float,
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_Cxw_Rhomb_M1.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}
    res_dict['x2'] = {}
    res_dict['x3'] = {}
    res_dict['x4'] = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x2 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x3 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x4 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_Cxw_Rhomb_M1(
        ctypes.byref(Result),
        ctypes.c_float(M),
        ctypes.c_float(cc),
        ctypes.c_float(zeta_c),
        ctypes.c_float(chi_c),
        ctypes.c_float(lambda_c),
        ctypes.byref(x4),
        ctypes.byref(x3),
        ctypes.byref(x2),
        ctypes.byref(x1),
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
        res_dict['x2']['Value'] = x2.Value
        res_dict['x2']['Min'] = x2.Min
        res_dict['x2']['Max'] = x2.Max
        res_dict['x3']['Value'] = x3.Value
        res_dict['x3']['Min'] = x3.Min
        res_dict['x3']['Max'] = x3.Max
        res_dict['x4']['Value'] = x4.Value
        res_dict['x4']['Min'] = x4.Min
        res_dict['x4']['Max'] = x4.Max
    return res_dict


def get_Sigma_pw(M, chi_c):
    """Функция для определения поправочного множителя, учитывающего степень влияния формы\\
    профиля на коэффициент волнового сопротивления несущей поверхности.

    Аргументы
    =========

        M: `float`
            Число Маха (аргумент 1). 
        chi_c: `float`
            Угол стреловидности по линии максимальных толщин крыла с данным профилем, рад (аргумент 2). 

    Выходные параметры
    ==================     

        'Result': `float`
            Поправочный множитель, учитывающий степень влияния формы профиля на коэффициент волнового сопротивления несущей поверхности.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======

        >>> print('Sigma_pw:')
        M = 1
        chi_c = 0
        Sigma_pw = get_Sigma_pw(
            M=M,
            chi_c=chi_c
        )
        print(f'M = {M}')
        print(f'chi_c = {chi_c}')
        print('Result =', Sigma_pw['Result'])
        print('x1_Min =', Sigma_pw['x1']['Min'])
        print('x1_Value =', Sigma_pw['x1']['Value'])
        print('x1_Max =', Sigma_pw['x1']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_Sigma_pw.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_Sigma_pw.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_Sigma_pw(
        ctypes.byref(Result),
        ctypes.c_float(M),
        ctypes.c_float(chi_c),
        ctypes.byref(x1),
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
    return res_dict


def get_Mcr_pr(cc, Cn, xx_c):
    """Функция для определения критического числа Маха для симметричных дозвуковых профилей.

    Аргументы
    =========

        cc: `float`
            Относительная толщина профиля (аргумент 1).  
        Cn: `float`
            Коэффициент нормальной силы консолей (аргумент 2).
        xx_c: `float`
            Относительная координата линии максимальных толщин (аргумент 3).

    Выходные параметры
    ==================     

        'Result': `float`
            Критическое число Маха профиля.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x2':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x3':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======

        >>> print('Mcr_pr:')
        cc = 0.1
        Cn = 0.04
        xx_c = 0.35
        Mcr_pr = get_Mcr_pr(
            cc=cc,
            Cn=Cn,
            xx_c=xx_c
        )
        print(f'cc = {cc}')
        print(f'Cn = {Cn}')
        print(f'xx_c = {xx_c}')
        print('Result =', Mcr_pr['Result'])
        print('x1_Min =', Mcr_pr['x1']['Min'])
        print('x1_Value =', Mcr_pr['x1']['Value'])
        print('x1_Max =', Mcr_pr['x1']['Max'])
        print('x2_Min =', Mcr_pr['x2']['Min'])
        print('x2_Value =', Mcr_pr['x2']['Value'])
        print('x2_Max =', Mcr_pr['x2']['Max'])
        print('x3_Min =', Mcr_pr['x3']['Min'])
        print('x3_Value =', Mcr_pr['x3']['Value'])
        print('x3_Max =', Mcr_pr['x3']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_Mcr_pr.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.c_float,
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_Mcr_pr.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}
    res_dict['x2'] = {}
    res_dict['x3'] = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x2 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x3 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_Mcr_pr(
        ctypes.byref(Result),
        ctypes.c_float(cc),
        ctypes.c_float(Cn),
        ctypes.c_float(xx_c),
        ctypes.byref(x3),
        ctypes.byref(x2),
        ctypes.byref(x1),
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
        res_dict['x2']['Value'] = x2.Value
        res_dict['x2']['Min'] = x2.Min
        res_dict['x2']['Max'] = x2.Max
        res_dict['x3']['Value'] = x3.Value
        res_dict['x3']['Min'] = x3.Min
        res_dict['x3']['Max'] = x3.Max
    return res_dict


def get_DELTA_Mcr0_lambda(Mcr_pr0, lambda_c):
    """Функция для определения поправки к критическому числу Маха, учитывающей конечность размаха несущей поверхности.

    Аргументы
    =========

        Mcr_pr0: `float`
            Относительная толщина профиля (аргумент 1).  
        lambda_c: `float`
            Относительная координата точки перехода\\
            ламинарного пограничного слоя в турбулентный (аргумент 2). 

    Выходные параметры
    ==================     

        'Result': `float`
            Поправка к критическому числу Маха, учитывающая\\
            конечность размаха несущей поверхности.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x2':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======

        >>> print('DELTA_Mcr0_lambda:')
        Mcr_pr0 = 0.9
        lambda_c = 1
        DELTA_Mcr0_lambda = get_DELTA_Mcr0_lambda(
            Mcr_pr0=Mcr_pr0,
            lambda_c=lambda_c
        )
        print(f'Mcr_pr0 = {Mcr_pr0}')
        print(f'lambda_c = {lambda_c}')
        print('Result =', DELTA_Mcr0_lambda['Result'])
        print('x1_Min =', DELTA_Mcr0_lambda['x1']['Min'])
        print('x1_Value =', DELTA_Mcr0_lambda['x1']['Value'])
        print('x1_Max =', DELTA_Mcr0_lambda['x1']['Max'])
        print('x2_Min =', DELTA_Mcr0_lambda['x2']['Min'])
        print('x2_Value =', DELTA_Mcr0_lambda['x2']['Value'])
        print('x2_Max =', DELTA_Mcr0_lambda['x2']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_DELTA_Mcr0_lambda.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_DELTA_Mcr0_lambda.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}
    res_dict['x2'] = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x2 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_DELTA_Mcr0_lambda(
        ctypes.byref(Result),
        ctypes.c_float(Mcr_pr0),
        ctypes.c_float(lambda_c),
        ctypes.byref(x2),
        ctypes.byref(x1),
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
        res_dict['x2']['Value'] = x2.Value
        res_dict['x2']['Min'] = x2.Min
        res_dict['x2']['Max'] = x2.Max
    return res_dict


def get_DELTA_Mcr0_chi(Mcr_pr0, chi_c):
    """Функция для определения поправки к критическому числу Маха, учитывающей стреловидность несущей поверхности.

    Аргументы
    =========

        Mcr_pr0: `float`
            Относительная толщина профиля (аргумент 1).  
        chi_c: `float`
            Угол стреловидности по линии максимальных толщин, рад (аргумент 2). 

    Выходные параметры
    ==================     

        'Result': `float`
            Поправка к критическому числу Маха, учитывающая стреловидность несущей поверхности.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x2':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======

        >>> print('DELTA_Mcr0_chi:')
        Mcr_pr0 = 0.9
        chi_c = 1.05
        DELTA_Mcr0_chi = get_DELTA_Mcr0_chi(
            Mcr_pr0=Mcr_pr0,
            chi_c=chi_c
        )
        print(f'Mcr_pr0 = {Mcr_pr0}')
        print(f'chi_c = {chi_c}')
        print('Result =', DELTA_Mcr0_chi['Result'])
        print('x1_Min =', DELTA_Mcr0_chi['x1']['Min'])
        print('x1_Value =', DELTA_Mcr0_chi['x1']['Value'])
        print('x1_Max =', DELTA_Mcr0_chi['x1']['Max'])
        print('x2_Min =', DELTA_Mcr0_chi['x2']['Min'])
        print('x2_Value =', DELTA_Mcr0_chi['x2']['Value'])
        print('x2_Max =', DELTA_Mcr0_chi['x2']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_DELTA_Mcr0_chi.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_DELTA_Mcr0_chi.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}
    res_dict['x2'] = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x2 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_DELTA_Mcr0_chi(
        ctypes.byref(Result),
        ctypes.c_float(Mcr_pr0),
        ctypes.c_float(chi_c),
        ctypes.byref(x2),
        ctypes.byref(x1),
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
        res_dict['x2']['Value'] = x2.Value
        res_dict['x2']['Min'] = x2.Min
        res_dict['x2']['Max'] = x2.Max
    return res_dict


def get_Cxdon_pr(M):
    """Функция для определения коэффициента донного сопротивления, создаваемого затупленной задней кромкой профиля несущей поверхности.

    Аргументы
    =========

        M: `float`
            Число Маха (аргумент 1). 

    Выходные параметры
    ==================     

        'Result': `float`
            Коэффициент донного сопротивления, создаваемого затупленной задней кромкой профиля несущей поверхности.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======

        >>> print('Cxdon_pr:')
        M = 2
        Cxdon_pr = get_Cxdon_pr(
            M=M
        )
        print(f'M = {M}')
        print('Result =', Cxdon_pr['Result'])
        print('x1_Min =', Cxdon_pr['x1']['Min'])
        print('x1_Value =', Cxdon_pr['x1']['Value'])
        print('x1_Max =', Cxdon_pr['x1']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_Cxdon_pr.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_Cxdon_pr.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_Cxdon_pr(
        ctypes.byref(Result),
        ctypes.c_float(M),
        ctypes.byref(x1),
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
    return res_dict


def get_Sigma_Cxinos(M, lambda_nos, key):
    """Функция для определения множителя, учитывающего форму носовой части и число Маха при расчёте\\
    коэффициента тангенциальной силы, индуцированной перераспределением давления на носовой части при ненулевых углах атаки.

    Аргументы
    =========

        M: `float`
            Число Маха (аргумент 1).  
        lambda_nos: `float`
            Удлинение носовой части фюзеляжа (аргумент 2). 
        key: `float`
            Ключ, определяющий тип носовой части (аргумент 3):\\
                key = 0 - коническая;\\
                key = 1 - оживальная;\\
                0 < key < 1 - интерполяция.

    Выходные параметры
    ==================     

        'Result': `float`
            Множитель, учитывающий форму носовой части и число Маха.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x2':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======

        >>> print('Sigma_Cxinos:')
        M = 1
        lambda_nos = 1
        key = 1
        Sigma_Cxinos = get_Sigma_Cxinos(
            M=M,
            lambda_nos=lambda_nos,
            key=key
        )
        print(f'M = {M}')
        print(f'lambda_nos = {lambda_nos}')
        print(f'key = {key}')
        print('Result =', Sigma_Cxinos['Result'])
        print('x1_Min =', Sigma_Cxinos['x1']['Min'])
        print('x1_Value =', Sigma_Cxinos['x1']['Value'])
        print('x1_Max =', Sigma_Cxinos['x1']['Max'])
        print('x2_Min =', Sigma_Cxinos['x2']['Min'])
        print('x2_Value =', Sigma_Cxinos['x2']['Value'])
        print('x2_Max =', Sigma_Cxinos['x2']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_Sigma_Cxinos.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.c_float,
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_Sigma_Cxinos.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}
    res_dict['x2'] = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x2 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_Sigma_Cxinos(
        ctypes.byref(Result),
        ctypes.c_float(M),
        ctypes.c_float(lambda_nos),
        ctypes.c_float(key),
        ctypes.byref(x2),
        ctypes.byref(x1),
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
        res_dict['x2']['Value'] = x2.Value
        res_dict['x2']['Min'] = x2.Min
        res_dict['x2']['Max'] = x2.Max
    return res_dict


def get_CC_F_IsP(M, lambda_c, chi_0):
    """Функция для определения коэффициента пропорциональности подсасывающей силы консолей несущей поверхности.

    Аргументы
    =========

        M: `float`
            Число Маха (аргумент 1).  
        lambda_c: `float`
            Удлинение консолей несущей поверхности (аргумент 2). 
        chi_0: `float`
            Угол стреловидности по передней кромке несущей поверхности, рад (аргумент 3).

    Выходные параметры
    ==================     

        'Result': `float`
            Коэффициент пропорциональности подсасывающей силы консолей несущей поверхности.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x2':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======

        >>> print('CC_F_IsP:')
        M = 1
        lambda_c = 1
        chi_0 = 0
        CC_F_IsP = get_CC_F_IsP(
            M=M,
            lambda_c=lambda_c,
            chi_0=chi_0
        )
        print(f'M = {M}')
        print(f'lambda_c = {lambda_c}')
        print(f'chi_0 = {chi_0}')
        print('Result =', lambda_c*CC_F_IsP['Result'])
        print('x1_Min =', CC_F_IsP['x1']['Min'])
        print('x1_Value =', CC_F_IsP['x1']['Value'])
        print('x1_Max =', CC_F_IsP['x1']['Max'])
        print('x2_Min =', CC_F_IsP['x2']['Min'])
        print('x2_Value =', CC_F_IsP['x2']['Value'])
        print('x2_Max =', CC_F_IsP['x2']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_CC_F_IsP.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.c_float,
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_CC_F_IsP.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}
    res_dict['x2'] = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x2 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_CC_F_IsP(
        ctypes.byref(Result),
        ctypes.c_float(M),
        ctypes.c_float(lambda_c),
        ctypes.c_float(chi_0),
        ctypes.byref(x2),
        ctypes.byref(x1),
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
        res_dict['x2']['Value'] = x2.Value
        res_dict['x2']['Min'] = x2.Min
        res_dict['x2']['Max'] = x2.Max
    return res_dict


def get_Sigma_CF(M, chi_0, alpha):
    """Функция для определения множителя, учитывающего\\
    неполноту реализации подсасывающей силы консолей несущей поверхности.

    Аргументы
    =========

        M: `float`
            Число Маха (аргумент 1).  
        chi_0: `float`
            Угол стреловидности по передней кромке несущей поверхности, рад  (аргумент 2). 
        alpha: `float`
            Угол атаки несущей поверхности, рад (аргумент 3).

    Выходные параметры
    ==================     

        'Result': `float`
            Множитель, учитывающий неполноту реализации\\
            подсасывающей силы консолей несущей поверхности.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x2':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======

        >>> print('Sigma_CF:')
        M = 1
        chi_0 = 0.79
        alpha = 0.1
        Sigma_CF = get_Sigma_CF(
            M=M,
            chi_0=chi_0,
            alpha=alpha
        )
        print(f'M = {M}')
        print(f'chi_0 = {chi_0}')
        print(f'alpha = {alpha}')
        print('Result =', Sigma_CF['Result'])
        print('x1_Min =', Sigma_CF['x1']['Min'])
        print('x1_Value =', Sigma_CF['x1']['Value'])
        print('x1_Max =', Sigma_CF['x1']['Max'])
        print('x2_Min =', Sigma_CF['x2']['Min'])
        print('x2_Value =', Sigma_CF['x2']['Value'])
        print('x2_Max =', Sigma_CF['x2']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_Sigma_CF.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.c_float,
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_Sigma_CF.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}
    res_dict['x2'] = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x2 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_Sigma_CF(
        ctypes.byref(Result),
        ctypes.c_float(M),
        ctypes.c_float(chi_0),
        ctypes.c_float(alpha),
        ctypes.byref(x2),
        ctypes.byref(x1),
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
        res_dict['x2']['Value'] = x2.Value
        res_dict['x2']['Min'] = x2.Min
        res_dict['x2']['Max'] = x2.Max
    return res_dict


def get_xi_M(M, lambda_nos, lambda_cil):
    """Функция для определения множителя, учитывающего влияние числа Маха на смещение фокуса комбинации носовой части и цилиндра.

    Аргументы
    =========

        M: `float`
            Число Маха (аргумент 1).  
        lambda_nos: `float`
            Удлинение носовой части фюзеляжа (аргумент 2). 
        lambda_cil: `float`
            Удлинение цилиндрической части фюзеляжа (аргумент 3).

    Выходные параметры
    ==================     

        'Result': `float`
            Множитель, учитывающий влияние числа Маха на\\
            смещение фокуса комбинации носовой части и цилиндра.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x2':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======

        >>> print('xi_M:')
        M = 1
        lambda_nos = 0.5
        lambda_cil = 2
        xi_M = get_xi_M(
            M=M,
            lambda_nos=lambda_nos,
            lambda_cil=lambda_cil
        )
        print(f'M = {M}')
        print(f'lambda_nos = {lambda_nos}')
        print(f'lambda_cil = {lambda_cil}')
        print('Result =', xi_M['Result'])
        print('x1_Min =', xi_M['x1']['Min'])
        print('x1_Value =', xi_M['x1']['Value'])
        print('x1_Max =', xi_M['x1']['Max'])
        print('x2_Min =', xi_M['x2']['Min'])
        print('x2_Value =', xi_M['x2']['Value'])
        print('x2_Max =', xi_M['x2']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_xi_M.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.c_float,
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_xi_M.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}
    res_dict['x2'] = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x2 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_xi_M(
        ctypes.byref(Result),
        ctypes.c_float(M),
        ctypes.c_float(lambda_nos),
        ctypes.c_float(lambda_cil),
        ctypes.byref(x2),
        ctypes.byref(x1),
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
        res_dict['x2']['Value'] = x2.Value
        res_dict['x2']['Min'] = x2.Min
        res_dict['x2']['Max'] = x2.Max
    return res_dict


def get_Coordinate_xxF_IsP(M, lambda_c, chi_05, zeta_c):
    """Функция для определения относительной координаты фокуса изолированной несущей поверхности.

    Аргументы
    =========

        M: `float`
            Число Маха (аргумент 1).  
        lambda_c: `float`
            Удлинение консолей (аргумент 2).
        chi_05: `float`
            Угол стреловидности по линии середин хорд, рад (аргумент 3).
        zeta_c: `float`
            Сужение консолей (аргумент 4).

    Выходные параметры
    ==================     

        'Result': `float`
            Относительная координата фокуса изолированной\\
            несущей поверхности.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x2':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }
        'x3':
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент. 
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======

        >>> print('Coordinate_xxF_IsP:')
        M = 1
        lambda_c = 1
        chi_05 = 0
        zeta_c = 1
        Coordinate_xxF_IsP = get_Coordinate_xxF_IsP(
            M=M,
            lambda_c=lambda_c,
            chi_05=chi_05,
            zeta_c=zeta_c
        )
        print(f'M = {M}')
        print(f'lambda_c = {lambda_c}')
        print(f'chi_05 = {chi_05}')
        print(f'zeta_c = {zeta_c}')
        print('Result =', Coordinate_xxF_IsP['Result'])
        print('x1_Min =', Coordinate_xxF_IsP['x1']['Min'])
        print('x1_Value =', Coordinate_xxF_IsP['x1']['Value'])
        print('x1_Max =', Coordinate_xxF_IsP['x1']['Max'])
        print('x2_Min =', Coordinate_xxF_IsP['x2']['Min'])
        print('x2_Value =', Coordinate_xxF_IsP['x2']['Value'])
        print('x2_Max =', Coordinate_xxF_IsP['x2']['Max'])
        print('x3_Min =', Coordinate_xxF_IsP['x3']['Min'])
        print('x3_Value =', Coordinate_xxF_IsP['x3']['Value'])
        print('x3_Max =', Coordinate_xxF_IsP['x3']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_Coordinate_xxF_IsP.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.c_float,
        ctypes.c_float,
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_Coordinate_xxF_IsP.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}
    res_dict['x2'] = {}
    res_dict['x3'] = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x2 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    x3 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_Coordinate_xxF_IsP(
        ctypes.byref(Result),
        ctypes.c_float(M),
        ctypes.c_float(lambda_c),
        ctypes.c_float(chi_05),
        ctypes.c_float(zeta_c),
        ctypes.byref(x3),
        ctypes.byref(x2),
        ctypes.byref(x1),
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
        res_dict['x2']['Value'] = x2.Value
        res_dict['x2']['Min'] = x2.Min
        res_dict['x2']['Max'] = x2.Max
        res_dict['x3']['Value'] = x3.Value
        res_dict['x3']['Min'] = x3.Min
        res_dict['x3']['Max'] = x3.Max
    return res_dict


def get_xi_D(DD):
    """Функция для определения множителя, учитывающего влияние\\
    относительного диаметра фюзеляжана координату приложения\\
    дополнительной нормальной силы консолей.

    Аргументы
    =========
    
        DD: `float`
            Относительный диаметр фюзеляжа в районе\\
            несущей поверхности (аргумент 1). 

    Выходные параметры
    ==================     

        'Result': `float`
            Множитель, учитывающий влияние относительного диаметра\\
            фюзеляжа на координату приложения дополнительной нормальной\\
            силы консолей.
        'x1': 
            `dict`: словарь следующего вида
                {
                    'Min': `float`
                        Первый выходной аргумент.
                    'Value': `float`
                        Второй выходной аргумент.
                    'Max': `float`
                        Третий выходной аргумент.
                }

    Пример
    ======

        >>> print('xi_D:')
        DD = 0.6
        xi_D = get_xi_D(
            DD=0.6
        )
        print(f'DD = {DD}')
        print('Result =', xi_D['Result'])
        print('x1_Min =', xi_D['x1']['Min'])
        print('x1_Value =', xi_D['x1']['Value'])
        print('x1_Max =', xi_D['x1']['Max'])
        print()
    """

    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_xi_D.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.POINTER(InputComplex),
    ]

    libstructpy.get_xi_D.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}
    res_dict['x1'] = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)

    x1 = InputComplex(
        ctypes.c_float(1),
        ctypes.c_float(2),
        ctypes.c_float(3),
    )

    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_xi_D(
        ctypes.byref(Result),
        ctypes.c_float(DD),
        ctypes.byref(x1),
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
        res_dict['x1']['Value'] = x1.Value
        res_dict['x1']['Min'] = x1.Min
        res_dict['x1']['Max'] = x1.Max
    return res_dict


def get_S_bok(D, S_nos, lambda_cil, lambda_cor, eta_cor, M, b_b, L_hv):
    """Функция для расчёта незатенённой площади боковой проекции фюзеляжа.

    Аргументы
    =========
    
        D: `float`
            Диаметр фюзеляжа, м (аргумент 1).
        S_nos: `float`
            Площадь боковой проекции носовой части фюзеляжа, м^2 (аргумент 2).
        lambda_cil: `float`
            Удлинение цилиндрической части фюзеляжа (аргумент 3).
        lambda_cor: `float`
            Удлинение кормовой части фюзеляжа (аргумент 4).
        eta_cor: `float`
            Сужение кормовой части фюзеляжа (аргумент 5).
        M: `float`
            Числа Маха набегающего потока на каждую несущую поверхность (аргумент 6).
        b_b: `float`
            Длины бортовых хорд несущих поверхностей, м (аргумент 7).
        L_hv: `float`
            Расстояния от концов бортовых хорд до донного среза фюзеляжа, м (аргумент 8).

    Выходные параметры
    ==================     

        'Result': `float`
            Незатенённая площадь боковой проекции фюзеляжа, м^2.

    Пример
    ======

        >>> print('S_bok:')
        D = 0.13
        S_nos = 1
        lambda_cil = 7.5
        lambda_cor = 0.769
        eta_cor = 0.811
        M = [1, 1.2]
        b_b = [0.24, 0.115]
        L_hv = [0.225, 0.1]
        S_bok = get_S_bok(
            D=D,
            S_nos=S_nos,
            lambda_cil=lambda_cil,
            lambda_cor=lambda_cor,
            eta_cor=eta_cor,
            M=M,
            b_b=b_b,
            L_hv=L_hv
        )
        print(f'D = {D}')
        print(f'S_nos = {S_nos}')
        print(f'lambda_cil = {lambda_cil}')
        print(f'lambda_cor = {lambda_cor}')
        print(f'eta_cor = {eta_cor}')
        print(f'M = {M}')
        print(f'b_b = {b_b}')
        print(f'L_hv = {L_hv}')
        print('Result =', S_bok['Result'])
        print()
    """
    
    M = Vector(M)
    b_b = Vector(b_b)
    L_hv = Vector(L_hv)
    
    #  Указание типов аргументов и возвращаемого значения
    libstructpy.get_S_bok.argtypes = [
        ctypes.POINTER(ctypes.c_float),
        ctypes.c_float,
        ctypes.c_float,
        ctypes.c_float,
        ctypes.c_float,
        ctypes.c_float,
        ctypes.c_void_p,
        ctypes.c_void_p,
        ctypes.c_void_p,
    ]

    libstructpy.get_S_bok.restype = ctypes.POINTER(ErrorCode)

    res_dict = {}

    #  Создание структур в Питоне
    #  Управление памятью Питоном
    Result = ctypes.c_float(1)
    
    res_1 = ErrorCode(
        ctypes.c_int(1),
        ctypes.c_int(1),
    )

    #  Вызов функций, описанных в DLL
    res_1 = libstructpy.get_S_bok(
        ctypes.byref(Result),
        ctypes.c_float(D),
        ctypes.c_float(S_nos),
        ctypes.c_float(lambda_cil),
        ctypes.c_float(lambda_cor),
        ctypes.c_float(eta_cor),
        M.vector,
        b_b.vector,
        L_hv.vector,
    )

    if res_1.contents.Code in ErrorMessageTable:
        raise ValueError(
            f'Аргумент {res_1.contents.ArgNumber}, {ErrorMessageTable[res_1.contents.Code]}.')
    else:
        res_dict['Result'] = Result.value
    return res_dict