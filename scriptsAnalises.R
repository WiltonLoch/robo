saidaCustoTotal <- read.table("saidaCustoTotal", stringsAsFactors=F)
saidaDestinosEscolhidos <- read.table("saidaDestinosEscolhidos", stringsAsFactors=F)
saidaMovimentosRealizados <- read.table("saidaMovimentosRealizados", stringsAsFactors=F)
saidaNosExpandidos <- read.table("saidaNosExpandidos", stringsAsFactors=F)

write.table(summary(saidaCustoTotal), file="analiseCustoTotal")
write.table(summary(saidaDestinosEscolhidos), file="analiseDestinosEscolhidos")
write.table(summary(saidaMovimentosRealizados), file="analiseMovimentosRealizados")
write.table(summary(saidaNosExpandidos), file="analiseNosExpandidos")
