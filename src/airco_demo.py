from airco import Airco


if __name__ == '__main__':
    print("Testing airco")
    a = Airco()
    print(f"After creation, airco state is {a.state.name}")

    print("Adding callback functions")
    f1 = lambda o_s, n_s: print(f"Transitioning from {o_s.name} to {n_s.name}")
    f2 = lambda o_s, n_s: print(f"I said.. {o_s.name} to {n_s.name}")
    a.AddCallback(f1)
    a.AddCallback(f2)

    a.On()
    a.Off()

