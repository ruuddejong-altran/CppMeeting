from airco import Controller


class PyController(Controller):
    def signal(self, event):
        print("[PyController] Received event:", event)
        Controller.signal(self, event)

    def handle_state_change(self):
        print("[PyController] Doing state change")
        Controller.handle_state_change(self)
