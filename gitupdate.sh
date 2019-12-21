#!/bin/bash

repositorio="git@github.com:iagolirapasssos/seguidor_com_PID_OBR.git"

#Inicializando o github
git init

#Dando um commit
git commit -m "$1"

#adicionando os arquivos ao repositorio
git add .

#Enviando ao repositorio remoto
git push origin "$repositorio"
