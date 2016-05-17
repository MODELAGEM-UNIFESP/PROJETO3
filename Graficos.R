getwd()
dados <- read.csv("SAIDA_REG.csv", header = F)
dados
matplot(dados[,(60:65)], type = "l")
erro = apply(dados[,(60:65)], 1, function(x) var(x))
matplot(erro, type="l")

dados <- read.csv("SAIDA_ER.csv", header = F)
matplot(dados[,(0:5)], type = "l")
erro = apply(dados[,(0:5)], 1, function(x) var(x))
matplot(erro, type="l")

dados <- read.csv("SAIDA_COM.csv", header = F)
matplot(dados[,(45:50)], type = "l")
erro = apply(dados[,(45:50)], 1, function(x) var(x))
matplot(erro, type="l")

dados <- read.csv("SAIDA_BA.csv", header = F)
matplot(dados[,(65:70)], type = "l")
erro = apply(dados[,(65:70)], 1, function(x) var(x))
matplot(erro, type="l")





