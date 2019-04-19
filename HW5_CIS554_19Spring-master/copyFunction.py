def copyFunction(file, oneFile):
    if (oneFile):
        studentSol = file
    else:
        studentSol = "Student1/" + file
    

    f = open(studentSol, "r")
    lines = list(f)
    f.close()

    f = open("template.cpp", "r")
    template = list(f)
    f.close()

    write_file = open("Tester/HW5.cpp", "w")
    toWrite = False
    write_file.write(lines[0])
    write_file.write(lines[1])
    write_file.write(lines[2])
    write_file.write(lines[3])
    write_file.write(lines[4])
    write_file.writelines(template)
    write_file.write("\n")

    for line in lines:
        
        if (line.find("ring::ring(int i, int j)") != -1 or 
            line.find("ring::~ring()") != -1 or
            line.find("ring::ring(const ring &r)") != -1 or
            line.find("ring::ring(ring &&r)") != -1 or
            line.find("void ring::operator=(ring &&r)") != -1 or
            line.find("void ring::operator=(const ring &r)") != -1 or
            line.find("ring::ring(const initializer_list<int> &V)") != -1 or
            line.find("int & ring::operator[](int a)") != -1 or
            line.find("int & ring::operator[](pair<int, int> p)") != -1 or
            line.find("void ring::DelCol(int i)") != -1 or
            line.find("ring ring::Threetimes()") != -1
            ):
            toWrite = True
        if (line == "}\n" and toWrite):
            toWrite = False
            write_file.write(line)
            continue

        if (toWrite):
            write_file.write(line)
    write_file.close()

    from shutil import copyfile

    filename = "".join(filter(str.isalnum, lines[1]))
    print("TESTING" + filename)
    # copyfile("Tester1/HW1.cpp", "StudentSols/" + filename + ".txt")

    # write_file = open("Result/" + filename + ".txt", "w")
    # write_file.write(lines[0])
    # write_file.write(lines[1])
    # write_file.write(lines[2])
    # write_file.write(lines[3])

    # write_file.close()