# ray-tracing

# Usage

use the following cli:

```bash
cd ray-tracing
cp Makefile.template Makefile
make all

```

For the documentation :

use `make docs`

# Description du projet

Ce projet a pour but de développer un outil de rendu d'image par la technique du tracé de rayon (ray tracing). L'objectif du projet est donc de développer une bibliothèque permettant le rendu d'image.

En l'état actuel, Le projet est capable de générer des objets tels que des sphères et des plans avec le modèle de réflection de Phong sans prendre totalement en compte la propriété de reflection ni de réfraction des objets. Il y a de plus une gestion simple des ombres par la méthode des shadow rays. Le ray-tracing comprend par ailleurs un moteur simple de rendu par multithreading en utilisant la bibliothèque openmp.

Ce qui aurait été souhaitable de faire dans ce projet est la gestion des triangles ainsi que d'un module permettant de travailler sur un fichier de description de scène en utilisant un format compatible avec d'autre logiciel de rendu de scène par exemple Blender. Il aurait été souhaitable de pouvoir prendre en compte la réfraction des objets.

Ce ray tracing prend mal en compte les propriétés de réflexion et de réfraction. Une amélioration possible est la prise en compte de ces effets. Une autre amélioration possible est l'utilisation d'un langage de description de scène pour permettre une utilisation plus aisée de l'outil. Par ailleurs, on utilise des scalaires pour caractériser les coefficients d'illumination des objets, une amélioration possible est d'utiliser des vecteurs pour pouvoir avoir un coefficient par couleur fondamentale.

# L'algorithme du moteur de rendu

L'algorithme utilisé par les moteurs est le suivant:

Étant donnée une scène qui comprend : un observateur, un écran, un ensemble d'objets visibles, un ensemble de source de lumière et une profondeur de récursion.

1 .Pour chaque pixel de l'écran faire partir un rayon, dont la couleur est celui de l'arrière plan, du centre du pixel et de direction la direction opposée de l'observateur.

2. Si un rayon touche un objet, le rayon prend la couleur de l'objet ainsi que l'illumination du point. Pour déterminer l'illumination on détermine l'ensemble des sources lumineuses atteignables. Si aucune source n'est atteignable le rayon prend la couleur noir. Si ensite la profondeur de récursion n'est pas atteinte alors on génère un rayon réfléchi et un rayon réfracté qui répèteront les mêmes étapes.

3. Lorsque tous les rayons ont été simulé, la couleur des pixels est mise à jours grâce à la couleur des rayons fondamentales.

## méthode de Phong pour la détermination de l'illumination d'un point.

L'illumination d'un point, \\(I_p\\) a été déterminé par la formule de Phong dont la formule est la suivante :

$$I_p = k_a i_a + \sum_{r \in sources} ( k_d (L_r \cdot N)\cdot i_{r,d} + k_s{( R_r \cdot  V)}^\alpha i_{r,s} )$$

avec :

- \\(k_s\\) la constant de réflexion spéculaire de l'objet,
- \\(k_d\\), la constante de diffusion reflexivede l'objet,
- \\(k_a\\), la constant de reflexion ambiant de l'objet,
- \\(\alpha\\), la constante de brillance de l'objet,
- \\(i_a\\), la lumière ambiante,
- \\(i_s\\), l'intensité spéculaire de la source lumineuse,
- \\(i_d\\), l'intensité de diffusion de la source lumineuse,
- \\(sources\\), l'ensemble des sources lumineuses accessibles,
- \\(L_r\\), le vecteur dirigé du point d'intersection vers la source,
- \\(N\\) la normale à la surface,
- \\(R_r\\), le rayon de reflexion parfait depuis la source \\(r\\),
- \\(V\\), le vecteur dirigé du point d'intersection vers l'observateur.

# Le format de sortie du programme

Le format des fichiers de sorties est le `.tga`.

# Les bibliothèques utilisées

Dans le cadre du projet, une bibliothèque pour la gestion des logs a été utilisée. Il s'agit de la librairie [spdlog](https://github.com/gabime/spdlog).
