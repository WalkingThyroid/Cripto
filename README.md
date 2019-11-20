# Cripto

[Ines]

peeps ai esta o codigo para algumas das funcionalidade do admin, gerar o certificado da CA, e gerar uma chave para o client bem como assinar a chave

usage : admin 1/0 (1 para gerar o certificado da CA , 0 para nao gerar) user_id

openssl dgst -sha256 -verify  <(openssl x509 -in user_id.crt  -pubkey -noout) -signature sign.txt.sha256 sign.txt
podes user este comando para verificar assinaturas

tens aqui um ballot box file com uma entrada assinada

os votos com a encriptação homomorfica ainda nao estão feitos mas isso n deve influenciar a assinatura

aconselho-te a estraires tudo do ficheiro de dados e depois escrever para um ficheiro o voto e para outro a assinatura e aplicares o comando

o formato é : user_id[:][espaço]Candidato1[espaço][votoencripitado]...Candidato10[espaço]Signature
Candidato10[espaço][votoencriptado][espaço]assinatura
*
also, falta ai a time_stamp que ainda nao foi implementada

ficaria após o user_id mas por agora n interessa mt

