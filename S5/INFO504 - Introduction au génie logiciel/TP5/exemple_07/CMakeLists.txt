# Commande devant "normalement" être présente pour vérifier la version de CMake utilisée
# Precise la version minimale pour assurer le bon fonctionnement de la génération de code
cmake_minimum_required(VERSION 3.0)

# Commande devant être présent dans le CMakeLists.txt de plus haut niveau
# Détaille le nom du projet et le cas échéant le langage associé
# Ici on précise le C++
project (HelloWorld CXX)

# Fixe la version du programme
set (HelloWorld_MAJOR_VERSION 1)
set (HelloWorld_MINOR_VERSION 7)

# Commande qui crée une variable locale
set (SRC src)
# Variable pour répertoire de headers
set (INC include)
# Variable pour répertoire de tests
set (TEST tests)

# Indique la transformation du .h.in en .h
configure_file(
  "${PROJECT_SOURCE_DIR}/${INC}/HelloWorld.h.in"
  "${PROJECT_BINARY_DIR}/${INC}/HelloWorld.h"
  )

# On ajoute le répertoire MyStrlen pour la recherche de header
include_directories ("${PROJECT_SOURCE_DIR}/MyStrlen")

# On ajoute le répertoire src pour la recherche de headers (celui de HelloWorld.h)
include_directories ("${PROJECT_BINARY_DIR}/${INC}")

# Commande qui donne le chemin vers un répertoire qui devrait aussi contenir un
# fichier CMakeList pour faire différentes choses ...
add_subdirectory(${SRC})
add_subdirectory(${TEST})

# On ira voir dans le répertoire pour compiler la librairie statique
add_subdirectory(MyStrlen)

# Permet la création de l'exécutable HelloWorld à partir du code source qui est dans le répertoire src
# Remarquez les {} pour avoir la valeur de la variable
add_executable(HelloWorld ${SRC}/HelloWorld.cxx)

# On fait l'édition de lien avec MyStrelen
target_link_libraries (HelloWorld  MyStrlen)

# Précise où il faut mettre l'exécutable HelloWorld
# Si on fait un install ==> dans un répertoire bin (de /usr/local sous linux)
# En cas d'utilisation de CPack, permet d'indiquer le répertoire à créer
# Pour mettre l'exécutable (bin dans l'exemple)
install(TARGETS HelloWorld RUNTIME DESTINATION bin)

# Ajoute aux besoins des librairies spécifiques nécessaire par le système hôte
include (InstallRequiredSystemLibraries)

# Indique la licence à utiliser
set (CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/License.txt")

# Indique la version du programme utilisé à reporter dans les paquetages
set (CPACK_PACKAGE_VERSION_MAJOR "${HelloWorld_MAJOR_VERSION}")
set (CPACK_PACKAGE_VERSION_MINOR "${HelloWorld_MINOR_VERSION}")

# Active la possibilité d'utiliser CPack
include(CPack)

