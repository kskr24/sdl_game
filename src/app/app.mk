bin/app: src/app/main.o lib/game.a
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDLIBS)
