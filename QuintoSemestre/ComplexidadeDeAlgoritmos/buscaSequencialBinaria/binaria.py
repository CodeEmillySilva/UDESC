def binariaSearch (lista, num, comeco=0, fim=None):

    if fim is None:
        fim = len(lista)-1

    if comeco <= fim:
        meio = (comeco+fim)//2

        if lista[meio]==num:
            return num

        if num<lista[meio]:
            return binariaSearch(lista, num, comeco,meio-1)
        else:
            return binariaSearch(lista,num,meio+1,fim)
    return None
