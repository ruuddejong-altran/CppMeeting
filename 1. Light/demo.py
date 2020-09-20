from light import Light


if __name__ == '__main__':
    print("Testing light")
    red = Light("red", Light.State.Off)
    print("Created light with name ", red.name)
    print(f"New light should be off. Actual state is {red.state.name}")
    red.state = Light.State.On
    print(f"Setting light on. Actual state is {red.state.name}")
    red.state = Light.State.Flashing
    print(f"Setting light flashing. Actual state is {red.state.name}")
    print()

