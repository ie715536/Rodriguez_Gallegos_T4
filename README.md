# Rodriguez_Gallegos_T4
Para la implementación de esta tearea utilizamos el systick para hacer la cuenta de segundos en el que incrementabamos las variables globales de segundos, minutos y horas. Para la implementación del systick que es lo que vale la pena de la tarea descubrimos que este tiene que ser dividido entre 1000 para lograr una cuenta en milisegundos por lo que después hacemos un delay con banderas en el handler del systick de 1000, para que al pasar mil milisegundos hiciera la cuenta en segundos. Una vez teniendo eso comparamos constantemente si nuestros valoes de segundos, minutos y horas son iguales a los de estructura alarma previamente inicializada. Cada cuenta de segundos se imprime la hora actual. 
