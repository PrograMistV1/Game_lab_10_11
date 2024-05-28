# Praca laboratoryjna 10-11

## Instalacja.
```
git clone https://github.com/PrograMistV1/Game_lab_10_11
cd ./Game_lab_10_11
mkdir cmake-build
cmake -B ./cmake-build
cmake --build ./cmake-build
```

## Krótkie instrukcje.
Aby program działał poprawnie należy go uruchomić w konsoli systemowej (konsola niektórych IDE nie działa poprawnie). Program działa na systemach Windows i Linux.
Nawigacja po menu gry odbywa się poprzez naciśnięcie strzałek ↑ i ↓ oraz enter na klawiaturze.

## Inwentarz.
W ekwipunku można przechowywać różne przedmioty, jego wielkość jest ograniczona. Wybierz przedmiot w swoim ekwipunku i naciśnij Enter, aby otworzyć menu przedmiotu. Przedmiot można odrzucić, przenieść do innego miejsca lub użyć.

## Pokoje.
W sumie są dwa pokoje, zwykłe(70%) i rzadkie(30%). W zwykłym pomieszczeniu znajduje się skrzynia zawierająca od 1 do 5 zwykłych przedmiotów. W rzadkim pokoju znajduje się skrzynia zawierająca tylko jeden rzadki przedmiot.
Pokoje możesz wyszukiwać tylko wtedy, gdy masz energię. Szansa na znalezienie pokoju wynosi 45%, na spotkanie potwora 25%, a na znalezienie niczego 25%. Jeśli zdrowie spadnie do 0, gra się zakończy.
Aby przywrócić zdrowie i energię, musisz skorzystać z przycisku odpoczynku lub skorzystać z przedmiotów znajdujących się w ekwipunku.
