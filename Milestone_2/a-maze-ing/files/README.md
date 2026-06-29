# A-Maze-ing

*This project has been created as part of the 42 curriculum by \<your_login\>.*

---

## Description

A-Maze-ing est un **générateur de labyrinthe en Python** qui :

- Lit un fichier de configuration (taille, entrée, sortie, graine aléatoire…)
- Génère un labyrinthe parfait ou imparfait avec l'algorithme **Recursive Backtracker (DFS)**
- Écrit le labyrinthe dans un fichier texte au format hexadécimal
- Affiche le labyrinthe dans le terminal avec couleurs ANSI
- Intègre un pattern "**42**" visible dans le labyrinthe
- Calcule et affiche le **chemin le plus court** (BFS)

---

## Instructions

### Prérequis

- Python 3.10 ou supérieur
- pip

### Installation des dépendances

```bash
make install
```

### Lancer le programme

```bash
make run
# ou directement :
python3 a_maze_ing.py config.txt
```

### Menu interactif

```
==== A-Maze-ing ====
1. Re-generate a new maze      → nouveau labyrinthe
2. Show/Hide path              → affiche/cache le chemin
3. Rotate wall colour          → change la couleur des murs
4. Quit                        → quitter
```

### Lancer les tests

```bash
python3 -m pytest tests/ -v
```

### Lint

```bash
make lint
```

### Nettoyer

```bash
make clean
```

---

## Format du fichier de configuration

```ini
# Commentaire (ligne ignorée)

WIDTH=20          # Largeur en nombre de cellules
HEIGHT=15         # Hauteur en nombre de cellules
ENTRY=0,0         # Coordonnées entrée (col,row)
EXIT=19,14        # Coordonnées sortie (col,row)
OUTPUT_FILE=output_maze.txt   # Fichier de sortie
PERFECT=True      # True = labyrinthe parfait (1 seul chemin)
SEED=42           # Graine aléatoire (reproductibilité)
ALGORITHM=backtracker         # backtracker ou prim
```

---

## Algorithme de génération

**Recursive Backtracker (DFS iteratif)**

1. Toutes les cellules commencent avec 4 murs fermés.
2. On part de la cellule d'entrée, on la marque visitée.
3. On choisit aléatoirement un voisin non visité, on supprime le mur entre eux.
4. On avance vers ce voisin. S'il n'y a plus de voisins non visités, on revient en arrière (backtrack).
5. On répète jusqu'à avoir visité toutes les cellules.

**Pourquoi ce choix ?**
- Simple à implémenter et à comprendre.
- Produit des labyrinthes avec de longs corridors sinueux (esthétique classique).
- Résultat garanti : arbre couvrant = labyrinthe parfait.
- Contrôle total via une graine aléatoire.

---

## Partie réutilisable (module mazegen)

Le module `mazegen` est un package Python installable séparément.

### Installation

```bash
pip install mazegen-2.2-py3-none-any.whl
# ou depuis les sources :
cd mazegen_pkg && python3 -m build && pip install dist/mazegen-2.2-py3-none-any.whl
```

### Utilisation de base

```python
from mazegen import MazeGenerator

# Créer et générer un labyrinthe 20x15
mg = MazeGenerator(
    width=20,
    height=15,
    entry=(0, 0),       # (col, row)
    exit_=(19, 14),
    perfect=True,
    seed=42,
)
mg.generate()

# Accéder au résultat
print(mg.grid)          # list[list[int]] – grille de bitmasks
print(mg.solution)      # str – chemin "SSEENNEE..."
print(mg.forty_two)     # set[tuple] – cellules du pattern "42"
```

### Paramètres disponibles

| Paramètre | Type | Description |
|-----------|------|-------------|
| `width`   | int  | Nombre de colonnes |
| `height`  | int  | Nombre de lignes |
| `entry`   | tuple(col, row) | Cellule d'entrée |
| `exit_`   | tuple(col, row) | Cellule de sortie |
| `perfect` | bool | True = 1 seul chemin |
| `seed`    | int \| None | Graine aléatoire |

### Lire la grille

```python
# grid[row][col] = entier 0–15 encodant les murs fermés
# bit 0 (LSB) = Nord, bit 1 = Est, bit 2 = Sud, bit 3 = Ouest
# 1 = mur fermé, 0 = mur ouvert

cell = mg.grid[0][0]
north_closed = (cell >> 0) & 1
east_closed  = (cell >> 1) & 1
south_closed = (cell >> 2) & 1
west_closed  = (cell >> 3) & 1
```

---

## Ressources

- [Maze generation algorithms – Wikipedia](https://en.wikipedia.org/wiki/Maze_generation_algorithm)
- [Recursive backtracker – Jamis Buck](https://weblog.jamisbuck.org/2010/12/27/maze-generation-recursive-backtracker)
- [BFS – Breadth-First Search](https://en.wikipedia.org/wiki/Breadth-first_search)
- [Python type hints – mypy](https://mypy.readthedocs.io/)
- [flake8 – style guide](https://flake8.pycqa.org/)

### Utilisation de l'IA

L'IA (Claude) a été utilisée pour :
- Proposer la structure initiale des modules (config, writer, display).
- Suggérer les cas de tests unitaires.
- Expliquer les subtilités du BFS et du backtracker DFS.

Tout le code a été relu, compris, corrigé et adapté manuellement.

---

## Gestion d'équipe

*(À compléter selon votre équipe)*

| Membre | Rôle |
|--------|------|
| login1 | Génération du labyrinthe, module mazegen |
| login2 | Affichage terminal, menu interactif |

**Planning** : 1 semaine – génération → tests → affichage → documentation.

**Ce qui a bien fonctionné** : le BFS est simple et fiable.
**À améliorer** : le pattern "42" peut couper des cellules accessibles.
