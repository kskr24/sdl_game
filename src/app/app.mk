bin/app: src/app/main.o lib/Game.a
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDLIBS)
