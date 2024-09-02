#TP8 SYSTEME Mini Projet
#Sarah Nguyen

import subprocess
import csv

liste_fichiers = subprocess.run(["ls eleves_bis"], shell=True, capture_output=True).stdout.decode()
liste_eleves = liste_fichiers.split('\n')
lst_7tests = [[0, 0, 0], [1, 0, 1], [0, 1, 1], [1, 1, 2], [12, 12, 24], [12, -43, -31], [-1, -52, -53]]


with open('csv_file', 'w') as f:
    writer = csv.writer(f)
    for e in liste_eleves[:-1]:
        lst = []
        nom_prenom = e[:-2].split('_')
        prenom = nom_prenom[0]
        nom = nom_prenom[1]
        lst.append(str(prenom))
        lst.append(str(nom))

        #compilation
        retour = subprocess.run([" gcc  -std=c17 -Wall eleves_bis/"+str(e)+" -o eleves_bis/"+prenom+"_"+nom], shell=True, capture_output=True).stderr
        
        #test est exécutable
        test1 = subprocess.run(["ls eleves_bis/"+prenom+"_"+nom], shell=True, capture_output=True).stderr
        if "impossible" in str(test1):
            executable = 0
        else:
            executable = 1
        lst.append(str(executable))

        #nombre de warning
        lst.append(str(retour).count("warning"))

        #7 tests lancés
        cmpt = 0
        for i in range(7):
            a = subprocess.run("./eleves_bis/" + prenom + "_" + nom + " " + str(lst_7tests[i][0]) + " " + str(lst_7tests[i][1]), shell=True, capture_output=True).stdout.decode()
            if (a == "La somme de " + str(lst_7tests[i][0]) + " et " + str(lst_7tests[i][1]) + " vaut " + str(lst_7tests[i][2]) +"\n"):
                cmpt += 1
        lst.append(str(cmpt))

        #nb lignes documentation
        nb_doc = (subprocess.run("cat eleves_bis/"+ str(e) +" | grep -e '*/' | wc -l", shell=True, capture_output=True).stdout.decode())
        lst.append(str(nb_doc[0]))

        writer.writerow(lst)
    
f.close()
    