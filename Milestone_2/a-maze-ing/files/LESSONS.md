# Leçons du projet A-Maze-ing — Explication complète

---

## LEÇON 1 — Représentation binaire et encodage hexadécimal

### Le problème
Chaque cellule du labyrinthe a 4 murs (Nord, Est, Sud, Ouest).
Comment stocker ces 4 informations en **1 seul caractère** ?

### La solution : les bits
Un entier est représenté en binaire : une suite de 0 et de 1.
On utilise **4 bits** (un par direction) :

```
Bit 3   Bit 2   Bit 1   Bit 0
Ouest   Sud     Est     Nord
```

Règle : **1 = mur fermé, 0 = mur ouvert**

### Exemples concrets

| Valeur décimale | Binaire | Hex | Murs fermés         |
|-----------------|---------|-----|---------------------|
| 0               | 0000    | 0   | aucun               |
| 15              | 1111    | F   | tous (cellule isolée)|
| 5               | 0101    | 5   | Nord + Sud          |
| 10              | 1010    | A   | Est + Ouest         |

### Comment lire/écrire un bit en Python

```python
# Lire le bit N d'une valeur v :
bit_N = (v >> N) & 1

# Mettre le bit N à 1 (fermer un mur) :
v = v | (1 << N)

# Mettre le bit N à 0 (ouvrir un mur) :
v = v & ~(1 << N)
```

### Exemple complet

```python
NORTH, EAST, SOUTH, WEST = 0, 1, 2, 3

cell = 0xA  # = 10 = 0b1010 → Est et Ouest fermés

print((cell >> NORTH) & 1)  # 0 → Nord ouvert
print((cell >> EAST)  & 1)  # 1 → Est FERMÉ
print((cell >> SOUTH) & 1)  # 0 → Sud ouvert
print((cell >> WEST)  & 1)  # 1 → Ouest FERMÉ
```

---

## LEÇON 2 — L'algorithme Recursive Backtracker (DFS)

### Intuition
Imaginez quelqu'un qui explore un labyrinthe en marquant chaque salle visitée.
Quand il est bloqué (toutes les salles voisines déjà visitées), il revient en arrière jusqu'à trouver une sortie non explorée.

### Étapes de l'algorithme
1. Toutes les cellules commencent avec **4 murs fermés**.
2. On choisit une cellule de départ, on la marque "visitée".
3. Tant qu'il reste des cellules non visitées :
   - Regarder les voisins non visités.
   - En choisir un au **hasard**.
   - **Supprimer le mur** entre la cellule actuelle et ce voisin.
   - Avancer vers ce voisin, le marquer visité.
   - Si plus de voisins → **reculer** (backtrack) d'une cellule.

### Pourquoi ça marche ?
L'algorithme construit un **arbre couvrant** du graphe de toutes les cellules.
Un arbre = pas de cycles = exactement **1 chemin** entre deux points → labyrinthe parfait !

### Code simplifié

```python
stack = [start_cell]
visited = {start_cell}

while stack:
    current = stack[-1]          # regarder le sommet de la pile
    neighbours = [voisins non visités de current]

    if neighbours:
        next_cell = random.choice(neighbours)
        remove_wall(current, next_cell)   # ouvrir le mur
        visited.add(next_cell)
        stack.append(next_cell)           # avancer
    else:
        stack.pop()                        # reculer (backtrack)
```

### Pourquoi une pile (stack) et pas la récursion ?
Python a une limite de récursion (~1000 appels).
Un labyrinthe de 20×15 = 300 cellules → on pourrait dépasser cette limite.
La pile itérative est identique mais **sans limite**.

---

## LEÇON 3 — BFS (Breadth-First Search)

### À quoi ça sert ici ?
Trouver le **chemin le plus court** de l'entrée à la sortie.

### Intuition
BFS explore le graphe **couche par couche** (comme des vagues dans l'eau).
La première fois qu'on atteint la destination, c'est forcément par le chemin le plus court.

### Comment ça marche

```
Entrée : cellule (0,0)
Niveau 0 : (0,0)
Niveau 1 : tous les voisins de (0,0) accessibles
Niveau 2 : tous les voisins des voisins non encore visités
...
```

### Code BFS complet commenté

```python
from collections import deque

def bfs(grid, entry, exit_):
    parent = {entry: None}   # pour reconstruire le chemin
    queue = deque([entry])

    while queue:
        current = queue.popleft()     # prendre le premier de la file
        if current == exit_:
            break                     # trouvé !

        row, col = current
        for direction in [NORTH, EAST, SOUTH, WEST]:
            if not wall_closed(grid, row, col, direction):   # mur ouvert ?
                neighbour = move(row, col, direction)
                if neighbour not in parent:
                    parent[neighbour] = (current, direction)  # mémoriser d'où on vient
                    queue.append(neighbour)

    # Reconstruire le chemin à l'envers
    path = []
    node = exit_
    while parent[node] is not None:
        prev, direction = parent[node]
        path.append(DIR_LETTER[direction])
        node = prev
    path.reverse()
    return "".join(path)
```

### DFS vs BFS
| | DFS (génération) | BFS (solution) |
|---|---|---|
| Structure | Pile (stack) | File (queue) |
| Ordre | Profondeur d'abord | Largeur d'abord |
| Résultat | Chemin quelconque | Chemin le **plus court** |

---

## LEÇON 4 — Graphes et théorie

### Un labyrinthe = un graphe
- **Nœuds** = cellules du labyrinthe
- **Arêtes** = passages entre cellules (murs ouverts)

### Labyrinthe parfait = arbre couvrant
Un **arbre couvrant** d'un graphe est un sous-graphe qui :
- Connecte **tous** les nœuds
- N'a **pas de cycles**
- A exactement **N-1 arêtes** pour N nœuds

→ Un labyrinthe parfait est exactement un arbre couvrant du graphe des cellules.
→ Il y a exactement **1 chemin** entre deux cellules quelconques.

### Labyrinthe imparfait = graphe avec cycles
On ajoute des arêtes supplémentaires → plusieurs chemins possibles.

---

## LEÇON 5 — Structure du projet Python (modules)

### Pourquoi séparer le code en modules ?
- **Lisibilité** : chaque fichier a une responsabilité claire.
- **Réutilisabilité** : `mazegen` peut être importé dans un autre projet.
- **Testabilité** : on teste chaque module indépendamment.

### Structure de ce projet

```
a_maze_ing/
├── a_maze_ing.py      ← programme principal (point d'entrée)
├── config.py          ← lecture et validation du fichier de config
├── writer.py          ← écriture du fichier de sortie
├── display.py         ← affichage terminal ANSI
├── config.txt         ← configuration par défaut
├── Makefile           ← automatisation des tâches
├── tests/
│   └── test_maze.py   ← tests unitaires
└── mazegen_pkg/       ← package pip installable
    ├── pyproject.toml
    └── mazegen/
        ├── __init__.py
        └── generator.py   ← classe MazeGenerator (réutilisable)
```

### Règle d'or
> Chaque module ne fait qu'**une chose** et la fait bien.

---

## LEÇON 6 — Créer un package Python installable (pip)

### Fichiers nécessaires

```
mazegen_pkg/
├── pyproject.toml       ← métadonnées du package
└── mazegen/
    ├── __init__.py      ← rend le dossier importable
    └── generator.py     ← code du module
```

### pyproject.toml minimal

```toml
[build-system]
requires = ["setuptools>=68", "wheel"]
build-backend = "setuptools.backends.legacy:build"

[project]
name = "mazegen"
version = "2.2"
requires-python = ">=3.10"
```

### Construire et installer

```bash
cd mazegen_pkg
pip install build
python3 -m build               # crée dist/mazegen-2.2-py3-none-any.whl
pip install dist/mazegen-2.2-py3-none-any.whl
```

### `__init__.py`
Ce fichier rend un dossier importable comme module Python.

```python
# mazegen/__init__.py
from .generator import MazeGenerator   # le "." = import relatif

__all__ = ["MazeGenerator"]  # ce qui est exporté avec "from mazegen import *"
```

---

## LEÇON 7 — Type hints et mypy

### Pourquoi des types ?
Python est dynamique (pas de types obligatoires), mais les **type hints** permettent :
- De documenter ce que fait une fonction.
- De détecter des bugs avec `mypy` avant d'exécuter le code.

### Syntaxe de base

```python
def add(a: int, b: int) -> int:
    return a + b

def parse(name: str) -> list[str]:
    return name.split(",")

from typing import Optional

def find(key: str) -> Optional[int]:  # peut retourner int ou None
    ...
```

### Types courants

| Type hint | Signification |
|-----------|---------------|
| `int` | entier |
| `str` | chaîne |
| `bool` | True/False |
| `list[int]` | liste d'entiers |
| `tuple[int, int]` | tuple de 2 entiers |
| `dict[str, int]` | dictionnaire str→int |
| `set[str]` | ensemble de chaînes |
| `Optional[int]` | int ou None |
| `None` | la fonction ne retourne rien |

### Lancer mypy

```bash
mypy . --disallow-untyped-defs --check-untyped-defs
```

---

## LEÇON 8 — Gestion des erreurs (exceptions)

### Principe
Ne jamais laisser le programme crasher sans message utile.

```python
# ✗ Mauvais
f = open("config.txt")    # crash si fichier absent : FileNotFoundError

# ✓ Bon
try:
    f = open("config.txt")
except FileNotFoundError:
    print("Erreur : fichier config.txt introuvable")
    sys.exit(1)
```

### Context managers (`with`)
Garantissent que le fichier est toujours fermé, même en cas d'erreur.

```python
# Ouverture automatiquement fermée
with open("maze.txt", "w") as f:
    f.write("contenu")
# f est fermé ici, même si une exception s'est produite
```

### Lever ses propres exceptions

```python
def parse_int(value: str) -> int:
    try:
        return int(value)
    except ValueError:
        raise ValueError(f"Valeur invalide : {value!r} (attendu un entier)")
```

---

## LEÇON 9 — Tests unitaires avec pytest

### Pourquoi tester ?
- Vérifier que le code fait ce qu'il est censé faire.
- Détecter les régressions (bugs introduits en modifiant le code).
- Documenter le comportement attendu.

### Structure d'un test

```python
def test_nom_descriptif() -> None:
    # Arrange – préparer les données
    mg = MazeGenerator(10, 10, (0,0), (9,9), True, 42)
    mg.generate()

    # Act – exécuter l'action à tester
    solution = mg.solution

    # Assert – vérifier le résultat
    assert len(solution) > 0
```

### Lancer les tests

```bash
python3 -m pytest tests/ -v      # verbose
python3 -m pytest tests/ -x      # s'arrêter au premier échec
```

### Classes de tests (regrouper par thème)

```python
class TestWallCoherence:
    """Tests de cohérence des murs."""

    def test_coherence_perfect(self) -> None:
        ...

    def test_coherence_small(self) -> None:
        ...
```

---

## LEÇON 10 — Affichage terminal avec les codes ANSI

### Qu'est-ce qu'un code ANSI ?
Des séquences de caractères spéciaux que le terminal interprète comme des commandes de couleur.

```python
RESET   = "\033[0m"    # revenir à la couleur normale
RED     = "\033[31m"   # texte rouge
BG_BLUE = "\033[44m"   # fond bleu
BOLD    = "\033[1m"    # texte gras
```

### Usage

```python
print(f"\033[42m\033[97m  E  \033[0m")   # fond vert, texte blanc, "E"
```

### Structure d'un affichage labyrinthe
Chaque cellule = **2 lignes × 2 colonnes** de caractères dans le terminal :

```
┌─┐   → ligne du haut : mur Nord
│ │   → ligne du milieu : mur Ouest, intérieur, mur Est
```

En répétant pour toutes les cellules et en ajoutant la ligne du bas finale, on obtient une grille.

---

## LEÇON 11 — Makefile

### À quoi ça sert ?
Automatiser les commandes répétitives en un mot.

### Syntaxe de base

```makefile
# Nom de la cible : dépendances
install:
	pip install flake8 mypy

run:
	python3 a_maze_ing.py config.txt

clean:
	find . -name "__pycache__" -exec rm -rf {} +
```

> **Attention** : l'indentation doit être avec une **tabulation** (TAB), pas des espaces.

### Utilisation

```bash
make install   # installe les dépendances
make run       # lance le programme
make clean     # nettoie les fichiers temporaires
```

---

## LEÇON 12 — Flake8 et le style de code (PEP 8)

### PEP 8 = le guide de style officiel Python

Règles principales :
- Indentation : **4 espaces** (pas de tabulations dans le code Python)
- Longueur de ligne : max **79 caractères**
- 2 lignes vides entre les fonctions/classes
- Noms de variables : `snake_case` (pas de camelCase)
- Constantes : `UPPER_CASE`

### Flake8 = l'outil de vérification

```bash
flake8 .              # vérifier tous les .py du projet
flake8 config.py      # vérifier un seul fichier
```

Erreurs courantes :
- `E302` : il manque 2 lignes vides avant une fonction
- `E501` : ligne trop longue (>79 caractères)
- `F401` : import inutilisé
- `W291` : espace en fin de ligne

---

## Résumé des concepts clés

| Concept | Où l'utiliser |
|---------|---------------|
| Bitmask (bits) | Encoder les murs des cellules |
| DFS / backtracker | Générer le labyrinthe |
| BFS | Trouver le chemin le plus court |
| Arbre couvrant | Comprendre ce qu'est un labyrinthe parfait |
| Modules Python | Organiser le code |
| Package pip | Rendre le code réutilisable |
| Type hints + mypy | Typer et vérifier le code |
| try/except | Gérer les erreurs proprement |
| with (context manager) | Gérer les fichiers |
| pytest | Tester le code |
| ANSI codes | Coloriser le terminal |
| Makefile | Automatiser les commandes |
| flake8 / PEP 8 | Respecter le style Python |
