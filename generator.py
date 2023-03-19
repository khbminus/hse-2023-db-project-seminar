from faker import Faker
import random

QUERIES = 1000

random.seed(566)
Faker.seed(566)

fake = Faker()

with open("entities.sql", "w") as f:
    for i in range(QUERIES):
        print(f"""INSERT INTO users(id, name, surname) VALUES(DEFAULT, '{fake.first_name()}', '{fake.last_name()}');""", file=f)
    for i in range(QUERIES):
        print(f"INSERT INTO manufacturers(id, name, country) VALUES(DEFAULT, '{fake.company()}', '{fake.country_code()}');",
              file=f)
    for i in range(QUERIES):
        print(f"INSERT INTO items(id, name, price, rating, manufacturer) "
              f"VALUES(DEFAULT, '{' '.join(fake.words())}', {random.randint(1, 5000)}, {random.random():.3f}, {random.randint(1, QUERIES)});",
              file=f)
    for i in range(QUERIES):
        print(f"INSERT INTO order_details(id, delivery_address) VALUES (DEFAULT, '{fake.address()}');", file=f)

with open("relations.sql", "w") as f:
    orders = list(range(1, QUERIES + 1))
    random.shuffle(orders)
    for i in orders:
        print(f"""INSERT INTO orders(customer_id, order_id) VALUES ({random.randint(1, QUERIES)}, {i});""", file=f)
    for i in orders:
        amount_of_items = random.randint(1, 10)
        items = list(range(1, QUERIES + 1))
        for item in random.choices(items, k=amount_of_items):
            print(f"INSERT INTO order_items(order_id, item_id) VALUES ({i}, {item});", file=f)

