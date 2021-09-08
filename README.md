# FSE 2021.01 - Controle de temperatura

O projeto em questão consiste em controlar a temperatura de um sistema fechado utilizando duas estratégias de controle(PID e ON/OFF). Define-se uma temperatura de referência por meio de um potenciômetro ou o terminal, e a temperatura interna do sistema deve adequar-se a temperatura do referência, aquecendo e resfriando via resistor e ventoinha.

| Aluno           | Matrícula  |
| --------------- | ---------- |
| Youssef Muhamad | 17/0024334 |

## Como rodar o projeto

1- Dentro da raspberryPI da disciplina, compile o projeto via make:

```sh
$ make
```

2- Após a compilação, o binário estará em `/bin/app`, execute-o:

```sh
$ ./bin/app
```

3- Agora basta seguir as perguntas que o programa fará :D.

![programa](https://user-images.githubusercontent.com/29265857/132424586-43ab2865-2f40-4e81-b7fe-1c763cd76279.gif)

## Resultados

### Controle ON/OFF

![on:off_potentiometer](https://user-images.githubusercontent.com/29265857/132424737-06c64d03-64e7-47a8-901b-3bc834bfff25.png)

![on:off_control_signal](https://user-images.githubusercontent.com/29265857/132424738-b2c7ce9b-3644-48e5-89f8-daf66f7a201e.png)

### Controle PID

![pid_potentiometer](https://user-images.githubusercontent.com/29265857/132424730-6926311d-8078-4607-a4d5-4e791de94a45.png)

![pid_control_signal](https://user-images.githubusercontent.com/29265857/132424734-53125912-4f67-4d22-8e67-13f292708fe2.png)
