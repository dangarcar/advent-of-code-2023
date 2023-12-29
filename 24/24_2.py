# In this one I almost gave up but in the end I used one solution that I understood from the solution Megathread
# Thanks to u/Weak_Swan7003 for the solution

import sympy as sp
X, Y, Z = 0, 1, 2

dx, dy, dz = sp.symbols('dx, dy, dz')
z, y, x = sp.symbols('z, y, x', positive=True, integer=True)

linear_system = []
for line in open('24.in'):
    # Get the input of the line
    pos, speed = line.strip().split('@')
    pos = [int(i) for i in pos.split(',')]
    speed = [int(i) for i in speed.split(',')]

    # Attach it to the list of equations
    linear_system.append(sp.Eq((pos[X] - x) * (dy - speed[Y]), (pos[Y] - y) * (dx-speed[X])))
    linear_system.append(sp.Eq((pos[X] - x) * (dz - speed[Z]), (pos[Z] - z) * (dx-speed[X])))

solved = sp.solve(linear_system, [dz, z, dy, y, dx, x])
[(dz, z, dy, y, dx, x)] = solved
ans = x + y + z

print(solved)
print(ans)