/* Функции для работы с input. */

/*
  int get_keyword_code(char **input_pt);

  Стек:
    main / get_keyword_code

  Функция get_keyword_code.
    (char **input_pt) уже считается ключевым словом.
    Принимает означенную строку и определяет ключевое слово, присваивая ему числовой код [1; 8]. Затем возвращает 
    данный код. Список кодов:
      1 - "=" (вывести на экран промежуточный итог).
      2 - "quit" (запрос на выход).
      3 - "c", clear (сброс).
      4 - "mca", clear all memory (обнулить все ячейки памяти).
      5 - "mpa", print all memory (вывести на экран все занятые ячейки памяти, т.е. отличные от 0).
      6 - "mr#", memory recall (получить число из #-й ячейки памяти).
      7 - "mc#", memory clear (обнулить #-ю ячейку памяти). (*)
      8 - "m+#", memory + (прибавить промежуточный итог к #-й ячейке).
      9 - "m-#", memory - (вычесть промежуточный итог из #-й ячейки).

    (*)
      Команды [5; 8] могут иметь вид не "mc#" ("mc1", "mc5"), а просто "mc" - в таком случае программа по умолчанию 
      обращается к 1-й ячейке памяти.
*/
int get_keyword_code(char **input_pt)
{
  int cell_ind = 0;
  register int count;
  char elem2 = *((*input_pt) + 1),
    elem3 = *((*input_pt) + 2);

  switch (**input_pt)
  {
    case 'q':
      return 1; // "quit"

    case '=':
      return 2; // "="

    case 'c':
      return 3; // "c"

    case 'm':
      if (elem2 == 'c' && elem3 == 'a')
        return 4; // "mca"

      else if (elem2 == 'p' && elem3 == 'a')
        return 5; // "mpa"

      else if (elem2 == 'r')
        return 6; // "mr"

      else if (elem2 == 'c')
        return 7; // "mc"

      else if (elem2 == '+')
        return 8; // "m+"

      else if (elem2 == '-')
        return 9; // "m-"
  }
}


/*   
  void reset_all_memcells(struct Memory *memory);

  Стек:
    main / reset_all_memcells

  Функция reset_all_memcells.
    Обнуляет все доступные ячейки памяти.
*/
void reset_all_memcells(struct Memory *memory)
{
  register int i;

  for (i = 0; i < MAX_SIZE; i++)
    memory -> cells[i] = 0.0;

  return;
}


/*   
  int type_is_num(char input_type);

  Стек:
    main / type_is_num

  Функция type_is_num.
    Если (char input_type) - символ 'n', возвращает 1.
    В противном случае возвращает 0.
*/
int type_is_num(char input_type)
{
  if (input_type == 'n')
    return 1;
  else
    return 0;
}


/* 
  int type_is_keyword(char input_type);

  Стек:
    main / type_is_keyword

  Функция type_is_keyword.
    Если (char input_type) - символ 'k', возвращает 1.
    В противном случае возвращает 0.
*/
int type_is_keyword(char input_type)
{
  if (input_type == 'k')
    return 1;
  else
    return 0;
}


/* 
  int type_is_operator(char input_type);

  Стек:
    main / type_is_operator

  Функция type_is_operator.
    Если (char input_type) - символ 'o', возвращает 1.
    В противном случае возвращает 0.
*/
int type_is_operator(char input_type)
{
  if (input_type == 'o')
    return 1;
  else
    return 0;
}


/*   
  int type_is_root(char input_type);

  Стек:
    main / type_is_root

  Функция type_is_root.
    Если (char input_type) - символ 'r', возвращает 1.
    В противном случае возвращает 0.
*/
int type_is_root(char input_type)
{
  if (input_type == 'r')
    return 1;
  else
    return 0;
}


/* 
  char * query_input();

  Стек:
    main / query_input

  Функция query_input.
    Производит запрос на ввод input и возвращает указатель на строку (т.е. указатель на данный input).
*/
char * query_input()
{
  static char input[MAX_SIZE];
  scanf("%s", input);

  return input;
}


/*
  double do_math(double subtotal, struct Input input);

  Стек:
    main / do_math

  Функция do_math.
    Возвращает результат вычислений.
*/
double do_math(double subtotal, struct Input input)
{
  /* 1. Объекты. */
  int exp_tmp = 0; // для case '^'

  /* 2. Вычисления. */
  switch (input.opr)
  {
    case '+':
      return subtotal + input.new_num;

    case '-':
      return subtotal - input.new_num;

    case '*':
      return subtotal * input.new_num;

    case '/':
      return subtotal / input.new_num;

    case '^':
      /* Конвертировать показатель степени в целое число. */
      /* И если принятый показатель отличается от преобразованного, предупредить об этом. */
      exp_tmp = input.new_num;
      if ((double) exp_tmp != input.new_num)
        printf("  Please note that exponent's been converted to %d.\n", exp_tmp);

      /* Число в степени 0 равно 1. */
      /* 0 в степени 0 - это, по сути, неопределенность, но по примеру того же стандартного калькулятора Windows
      0 в степени 0 сделаем 1. */
      if (!input.new_num)
        return 1.0;

      /* Если показатель степени - отриц. число, воспользоваться формулой (a / b) ^ -n == (b / a) ^ n
      Число b нашем случае можно автоматом принять за 1. */
      else if (input.new_num < 0)
        return 1 / (pow(subtotal, alter_num_sign(exp_tmp)));

      else
        return pow(subtotal, exp_tmp);

    case 'r':
      return sqrt(input.tmp);
  }
}


/* 
  char get_operator(char **input_pt);

  Стек:
    main / get_operator

  Функция get_operator.
    (char **input_pt) уже считается оператором.
    Принимает означенную строку и возвращает оператор.
*/
char get_operator(char **input_pt)
{
  return **input_pt; // получить 1-й элемент строки
}


/* 
  double get_num(char **input_pt);

  Стек:
    main / get_num
    main / get_keyword_code / get_num

  Функция get_num.
    (char **input_pt) уже считается числом.
    Принимает означенную строку и "сооружает" из нее значение типа double.
*/
double get_num(char **input_pt, double subtotal)
{
  /* 1. Объекты. */
  /* Состояния для корректного представления результата. */
  struct Input input;
  input.has_percent = 0;
  input.has_point = 0;
  
  char elem = '\0'; // псевдоним для **input_pt внутри цикла

  char sign = '\0'; // знак числа (если указан)
  double result = 0.0, // итоговое число
    multiplier = 1.0, // множитель
    remainder = 1.0, // остаток для десятичной дроби
    tmp = 0.0; // "промежуточный результат" для result

  /* 2. Определение знака числа. */
  register char *start = *input_pt;

  if (is_sign(**input_pt)) // есть знак?
  {
    sign = **input_pt; // если указан знак, запомнить его
    (*input_pt)++; // и перешагнуть данный элемент
  }

  /* 3. Перебор input, "создание" числа. */
  while ( (elem = **input_pt) != '\0' )
  {
    /* Если натыкаемся на точку, фиксируем это и пропускаем ее (ее наличие отразится в дальнейшем 
    на переменной remainder). */
    /* Если натыкаемся на символ '%', также фиксируем это и пропускаем данный элемент. */
    if ( ( !input.has_point && (input.has_point = is_point(elem)) ) ||
    ( !input.has_percent && (input.has_percent = is_percent(elem)) ))
    {
      (*input_pt)++;
      continue;
    }

    tmp = (double) (elem - (double) ASCII_IND_ZERO) / multiplier;
    result += tmp;

    /* Если есть точка (т.е. input - десятичная дробь). */
    if (input.has_point) // начать отсчет remainder начиная с элемента '.' для того
      remainder *= 10.0; // чтобы получить остаток

    multiplier *= 10; 
    
    (*input_pt)++;
  }

  *input_pt = start;

  /* 3. "Дошлифовка" результата. */
  result *= (multiplier / 10); // компенсировать лишнюю операцию multiplier *= 10

  if (input.has_point) // если число - десятичная дробь
    result /= remainder;

  if (sign == '-') // прописать нужный знак числу
    result = alter_num_sign(result);

  /* 4. Результат. */
  if (input.has_percent)
  {
    if (!subtotal)
      printf("  Please note that percantage of nothing is 0.");

    return get_percentage(subtotal, result);
  }

  else
    return result;
}


/* 
  int input_is_keyword(char ***input_pt);

  Стек:
    main / identify_input / input_is_keyword 

  Функция input_is_keyword.
    Если (char ***input_pt) - ключевое слово, возвращает 1.
    В противном случае возвращает 0.
*/
int input_is_keyword(char ***input_pt)
{
  /* 1. Объекты. */
  char input_str[MAX_SIZE]; // "mc10"
  char input_str_lpart[MAX_SIZE]; // подстрока input_str - часть с буквами

  struct Input strings;
  strings.are_identical = 0;

  /* Список ключевых слов. */
  char *sample_strings[SAMPLE_ARR_SIZE];
  sample_strings[0] = "=";
  sample_strings[1] = "quit";
  sample_strings[2] = "c";
  sample_strings[3] = "mr";
  sample_strings[4] = "mc";
  sample_strings[5] = "m+";
  sample_strings[6] = "m-";
  sample_strings[7] = "mca";
  sample_strings[8] = "mpa";

  char elem = ***input_pt;
  char *start = **input_pt;
  register int i,
    j;

  /* 2. 1-я фаза проверки. */

  /* 2.1. 1-й символ строки: '=', 'q', 'c' или 'm'? */
  for (i = 0; i < SAMPLE_ARR_SIZE; i++)
    if ( ( ***input_pt == sample_strings[i][0] ) &&
      (strings.are_identical = 1) ) {} // если нет, то дальше и проверять не стоит

  if (!strings.are_identical)
    return 0;

  /* 2.2. Получить строку input_str из текущего input'а для дальнейших испытаний. */
  /* Дальше будем работать с данной строкой, а не с указателем. */
  i = 0;

  while ((elem = ***input_pt) != '\0')
  {
    input_str[i] = elem;

    (**input_pt)++;
    i++;
  }

  input_str[i] = '\0';
  **input_pt = start;
  elem = ***input_pt;

  /* 2.3. Если input - "=", "quit" или "c". */
  if (elem != 'm')
  {
    strings.are_identical = 0;

    for (i = 0; i < SAMPLE_ARR_SIZE; i++)
      if ( !strcmp(sample_strings[i], input_str) &&
        (strings.are_identical = 1) ) {}

    if (!strings.are_identical)
      return 0;
    else
      return 1; // если input равен "=", "quit" или "c", все ok
  }
  /* 2.3. Если input - "mca" или "mpa". */
  else if ( (!strcmp(input_str, sample_strings[7]) || !strcmp(input_str, sample_strings[8])) )
    return 1;

  /* 3. 2-я фаза проверки. */

  /* 3.1. Идентичны ли sample_str и input_str (1-я половина)? */
  /* Например, есть такой input: "mc10" (memory clear, применить к ячейке под индексом 10). */
  strings.are_identical = 0;

  /* Получить первые 2 символа, т.е. взять подстроку "mc". */
  for (i = 0; i < 2; i++)
    input_str_lpart[i] = input_str[i];

  input_str_lpart[i] = '\0';

  /* Сравнить взятую выше подстроку с sample_str. */
  for (j = 0; j < SAMPLE_ARR_SIZE; j++) // i следует приберечь для проверки остатка input_str
    if ( !strcmp(input_str_lpart, sample_strings[j]) && (strings.are_identical = 1) ) {}; 
    // здесь "mc" идентично "mc", все правильно
    
  if (!strings.are_identical)
    return 0;

  /* 3.2. Проверка на корректность "индексной" части input_str, если таковая есть. */
  strings.are_identical = 0;

  /* Присмотреться к 1-му символу. */
  if ( input_str[i] && (!is_digit(input_str[i]) || input_str[i] == ASCII_IND_ZERO))
  // input вида "mc0" или "mc0010" не допускается
  // input вида "mc", т.е. {'m', 'c', '\0'}, допускается
    return 0; 

  i += 1;

  /* Если "индексная" часть - целое число вроде "10" (как в нашем примере), ввод, наконец, признается ключевым словом. */
  for (i; i < get_str_length(input_str); i++)
    if (!is_digit(input_str[i]))
      return 0;

  return 1;
}


/* 
  int input_is_number(char ***input_pt);

  Стек:
    main / identify_input / input_is_number 

  Функция input_is_number.
    Если (char ***input_pt) - число, возвращает 1. (*)
    В противном случае возвращает 0. 

    (*) Числом может также считаться input вида "50%" - на этапе get_num будет преобразован в нужный вид.
*/
int input_is_number(char ***input_pt)
{
  /* 1. Объекты. */
  struct Input input;
  input.has_percent = 0;
  input.has_point = 0;

  char elem = '\0'; // псевдоним для ***input_pt внутри цикла

  /* 2. Перебор input. */
  register char *start = **input_pt;

  if (is_percent(***input_pt))
    return 0; // число не может начинаться с символа '%'

  if (is_sign(***input_pt))
    (**input_pt)++; // если есть знак ('-' или '+'), перешагнуть его - пока никак не обрабатывать

  while ( (elem = ***input_pt) != '\0')
  {
    /* Если в input более одной точки '.', значит, input - не число. Вернуть 0. */
    /* Тем не менее input вроде ".2" или "2." допустим (такие числа будут интерпретироваться как 
    0.2 или 2.0 соответственно, как у JS). */
    if (is_point(elem) && input.has_point)
    {
      **input_pt = start;
      return 0;
    }  

    /* Элемент - точка? Определяется 1-я (и единственная допустимая) точка. */
    if ( !input.has_point && (input.has_point = is_point(elem)) )
    {
      (**input_pt)++;
      continue; 
    }

    /* Элемент - '%' или цифра? Если ни одно из двух, вернуть 0. */
    else if ( !( 
      !input.has_percent && (input.has_percent = is_percent(elem)) || // (1)
      is_digit(elem) // (2)
    ))
    /* 1) Если элемент - '%', ok, зафиксировать это. Символ '%' должен быть в ед. ч. */
    /* 2) Или: элемент - цифра? */
    {
      **input_pt = start;
      return 0;
    }

    (**input_pt)++;
  }

  /* Символ '%' должен быть последним значащим элементом массива, например: {'5', '%', '/0'} */
  if ( input.has_percent && !is_percent( *((**input_pt) - 1) ))
    return 0;

  **input_pt = start;

  return 1;
}


/* 
  int input_is_operator(char ***input_pt);

  Стек:
    main / identify_input / input_is_operator

  Функция input_is_operator.
    Если (char ***input_pt) - оператор, возвращает 1. 
    В противном случае возвращает 0. 
*/
int input_is_operator(char ***input_pt)
{
  /* 1. Объекты. */
  char operators_list_src[MAX_SIZE] = {/*'=',*/ '+', '-', '*', '/', '^', '\0'};
  char *operators_list; // будем пользоваться данным указателем вместо строки src
  // for no particular reason, разминки ради

  /* 2. Привести operators_list в соответствие с src. */
  init_mem(&operators_list, get_str_length(operators_list_src) + 1); // плюс 1 байт под нулевой терминатор
  fill_list_pt(&operators_list, operators_list_src);

  /* 3. Перебор символов input, перебор символов operators_list: */
  register char *start_input = **input_pt;
  register char *start_operators_list = operators_list;  

  while (*operators_list != '\0')
  {
    /* Проверить, является ли 1-й элемент input оператором. */
    if ( *operators_list == ***input_pt )
    {
      /* Если является - сдвинуть указатель на input на 1 вправо, ко 2-му элементу, и прервать цикл. */
      (**input_pt)++;
      break;
    }

    operators_list++;
  }

  operators_list = start_operators_list;
  free(operators_list); // высвободить память после init_mem

  /* 4. Результат. */

  /* 4.1. Если 2-й элемент input - нулевой терминатор, значит, это оператор. */
  if (***input_pt == '\0')
  /* Прим. input вроде " + -  *" будет считаться верным, поскольку scanf останавливается на первом же пробеле после 
  значащего элемента, и таким образом получает следующую строку: {'+', '\0'}, что есть '+' */
  {
    **input_pt = start_input;
    return 1;
  }

  /* 4.2. Если 2-й элемент input - не '\0', значит, это не оператор. Вернуть 0. */
  else
  {
    **input_pt = start_input;
    return 0;
  }
}


/* 
  int input_is_root(char ***input_pt);

  Стек:
    main / identify_input / input_is_root

  Функция input_is_root.
    Если (char ***input_pt) - корень 'r', возвращает 1. 
    В противном случае возвращает 0. 
*/
int input_is_root(char ***input_pt)
{
  register char *start = **input_pt;

  if ( (***input_pt == 'r') && !(*((**input_pt) + 1)) )
  {
    **input_pt = start;
    return 1;
  }

  **input_pt = start;
  return 0;
}


/* 
  char identify_input(char **input_pt, double subtotal, struct Input input);

  Стек:
    main / identify_input

  Функция identify_input.
    Если (char **input_pt) - ключевое слово, возвращает 'k' (keyword).
    Если (char **input_pt) - число, возвращает 'n' (number).
    Если (char **input_pt) - мат. оператор ('+', '*', ...), возвращает 'o' (operator).
    Если (char **input_pt) - корень (квадратный) 'r', возвращает 'r' (root).
    Если (char **input_pt) - некорректный ввод, возвращает '\0' (false).
*/
char identify_input(char **input_pt, double subtotal, struct Input input)
{
  /* 1. Объекты. Состояния. */
  struct Input input_state;
  input_state.is_keyword = 0;
  input_state.is_num = 0;
  input_state.is_operator = 0;
  input_state.is_root = 0;

  /* 2. Результат. Определение типа input ('x', 'n', 'o', 'r' или '\0'). */
  if (input_state.is_keyword = input_is_keyword(&input_pt))
    return 'k';

  else if (input_state.is_root = input_is_root(&input_pt))
    return 'r';

  else if (input_state.is_operator = input_is_operator(&input_pt))
    return 'o';

  else if (input_state.is_num = input_is_number(&input_pt))
    return 'n';
    
  /* Если input некорректный (не соотв. ни одному типу). */
  if ( (!input_state.is_keyword && 
    !input_state.is_root && 
      !input_state.is_operator && 
        !input_state.is_num) )
    return '\0';
}