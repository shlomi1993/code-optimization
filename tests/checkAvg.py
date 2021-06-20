with open("res.txt", "r") as file:
    data = file.read()
sum = 0
cnt = 0
data = data.split("\n")
for line in data:
    if line.startswith("Total runtime"):
        splitted = line.split(":")
        splitted = splitted[1].split(" ")
        sum += float(splitted[1])
        cnt = cnt + 1
print(sum / cnt)
        