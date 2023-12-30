import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation


baseFilePath = 'D:\\Mustafa\\MBEngine\\FlowSolver\\build\\Debug\\'

# Set up the figure and axis
fig, ax = plt.subplots()
line, = ax.plot([], [], lw=2)
ax.set_xlabel('X')
ax.set_ylabel('Convected Quantity')
ax.set_title('Linear Convection')

def animate1D(timestep):
    filePath = baseFilePath + 'field' + str(timestep) + '.txt'
    with open(filePath, 'r') as file:
        lines = file.readlines()

    # Extract the data from the file
    y_data = []
    for line in lines:
        if not line.startswith('Time') and not line.startswith('x'):
            columns = line.split()
            y_value = float(columns[3])
            y_data.append(y_value)

    # Update the plot
    ax.clear()
    plotted = ax.plot(y_data)
    ax.set_xlabel('X')
    ax.set_ylabel('Convected Quantity')
    ax.set_title('Linear Convection')
    return plotted

# Create the animation
animation = FuncAnimation(fig, animate1D, frames=24, interval=200, blit = True, repeat = False)

# Save the animation as a GIF file
animation.save('animation.gif', writer='pillow')

# Display the animation
plt.show()