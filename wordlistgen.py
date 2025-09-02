name=input("Enter name of Target: ")
with open("passwords.txt","w")as f:
    for i in range(9999):
        password=f"{name}{i}"
        print(password)
        f.write(f"{password}\n")
        