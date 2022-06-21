- combine the grid with the line model
- the grid should have a reference to its model that is likely to be in the renderer
- Line model repository for Line models from the grid and other line models

# Grid #
- Stores the intrisic properties of the grid
- position
- rows
- columns

#  Grid Modeller #
- Every frame it checks if the grid has changed
- If it has changed then it will edit it's associated line model

# Line Model #
- The grid is rendered as a line model,
- A line model is a vertex buffer that has been constructed from a list of floats that represent a list of lines.