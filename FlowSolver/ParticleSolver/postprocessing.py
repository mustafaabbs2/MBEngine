import pyvista as pv
from pyvista import examples
import numpy as np


def display_point_cloud():
    point_cloud = np.random.random((100, 3))
    pdata = pv.PolyData(point_cloud)
    pdata["orig_sphere"] = np.arange(100)
    sphere = pv.Sphere(radius=0.02, phi_resolution=10, theta_resolution=10)
    pc = pdata.glyph(scale=False, geom=sphere, orient=False)
    pc.plot(cmap="Reds")


def display_point_cloud_animation():
    num_frames = 5
    point_cloud = np.random.random((100, 3))
    pdata = pv.PolyData(point_cloud)
    pdata["orig_sphere"] = np.arange(100)
    sphere = pv.Sphere(radius=0.02, phi_resolution=10, theta_resolution=10)

    # Create a plotter
    p = pv.Plotter()

    # Loop through frames and update the point cloud position
    for i in range(num_frames):
        pdata.points[:, 0] += 0.01  # Move the points in the x-direction
        pc = pdata.glyph(scale=False, geom=sphere, orient=False)

        # Clear the plotter for each frame
        p.clear()

        # Add the point cloud and frame number text to the plot
        p.add_text(f"Frame: {i}", position="upper_left", font_size=18, color="black")

        # Render the plot
        p.render()

    # Show the animation
    p.show()


def make_cube():
    x = np.linspace(-0.5, 0.5, 25)
    grid = pv.StructuredGrid(*np.meshgrid(x, x, x))
    surf = grid.extract_surface().triangulate()
    surf.flip_normals()
    return surf


def display_cube_mesh():
    cube = make_cube()
    # Create mesh grid for visualization
    x = np.linspace(-0.5, 0.5, 25)
    grid_mesh = pv.StructuredGrid(*np.meshgrid(x, x, x)).extract_surface().triangulate()
    grid_mesh.flip_normals()

    p = pv.Plotter()
    p.add_mesh(cube, color="cyan", opacity=0.5)
    p.add_mesh(grid_mesh, color="gray", opacity=0.2, style="wireframe")
    p.show()
