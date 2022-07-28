///
/// stochastic.h
///
/// Generadores de numeros aleatorios para simulaciones estocasticas
///

/// cambia la semilla de generacion de numeros aleatorios
/// retorna el valor de la semilla anterior
/// new_seed: la nueva semilla, que reemplaza la anterior
double reset_seed(double new_seed);

/// genera un numero aleatorio entre 0 y 1
double uniform();

/// genera un numero aleatorio de acuerdo a una distribucion normal estandar
double normal();

/// retorna entero aleatorio k tal que lb <= k < ub
/// lb: (por "lower bound") la cota inferior, incluida en el rango de numeros aleatorios posibles
/// ub: (por "upper bound") la cota superior, excluida del rango de numeros aleatorios posibles
int random_int(int lb, int ub);
