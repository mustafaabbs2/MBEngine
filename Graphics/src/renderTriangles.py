import open3d as o3d

# Function to read and visualize the .ply file
def visualize_ply(file_path):
    # Read the PLY file
    mesh = o3d.io.read_triangle_mesh(file_path)
    
    # Check if the file is loaded correctly
    if not mesh.has_triangles():
        print(f"Failed to load {file_path}. Make sure it is a valid .ply file.")
        return

    # Print basic information about the mesh
    print(f"Loaded mesh from {file_path}")
    print(f"Vertices: {len(mesh.vertices)}")
    print(f"Triangles: {len(mesh.triangles)}")
    
    # Visualize the mesh
    o3d.visualization.draw_geometries([mesh])

# Example usage
file_path = "output.ply"  # Replace with your PLY file path
visualize_ply(file_path)
