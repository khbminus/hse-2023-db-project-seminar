# Postgres
```shell
sudo apt install postgresql postgresql-contrib
sudo systemctl start postgresql.service # или /etc/init.d/postgresql start
sudo -i -u postgres
psql # должны успешно зайти, после этого \q
createuser --interactive # ваше имя в системе
createdb <ваше имя>
```
# libpqxx
```shell
# считаем, что всё, что нужно для лаб у вас стоит
sudo apt install libpq-dev
git clone https://github.com/jtv/libpqxx.git
cd libpqxx
cmake . && cmake --build . && sudo cmake --install .
```
