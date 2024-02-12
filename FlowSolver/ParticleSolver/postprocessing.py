import pyvista as pv
from pyvista import examples
import numpy as np
import sys
import pandas as pd
import os
from pyvistaqt import BackgroundPlotter

# replace with path to lib
sys.path.insert(
    0,
    "D:\\Mustafa\\MBEngine\\MBEngine\\build\\Debug\\FlowSolver\\ParticleSolver\\Debug",
)

import particle_module as pm

base_path = (
    "D:\\Mustafa\\MBEngine\\MBEngine\\build\\Debug\\FlowSolver\\ParticleSolver\\Debug"
)

file_name = "particle_data_step_4.txt"

file_names = [
    "particle_data_step_0.txt",
    # "particle_data_step_1.txt",
    # "particle_data_step_2.txt",
    # "particle_data_step_4.txt",
]

# bg_plotter = BackgroundPlotter()


for file_name in file_names:
    file_path = os.path.join(base_path, file_name)
    df = pd.read_csv(file_path, delim_whitespace=True)
    df["Z"] = 0
    point_cloud = df[["X", "Y", "Z"]].values
    print(point_cloud.shape)
    pdata = pv.PolyData(point_cloud)
    sphere = pv.Sphere(radius=0.02, phi_resolution=10, theta_resolution=10)
    pc = pdata.glyph(scale=False, geom=sphere, orient=False)
    pc.plot(cmap="Reds")

    # bg_plotter.add_mesh(pc, cmap="Reds", show_scalar_bar=False)


def main():
    a = pm.get_array()
    print(a)


# bg_plotter.show()
