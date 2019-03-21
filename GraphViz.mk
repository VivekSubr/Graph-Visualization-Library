.PHONY: debug release run 

debug: BUILD_TYPE+=debug
debug: run

release: BUILD_TYPE+=release
release: run

run: 
	(cd Graphs;    $(MAKE) -B -f GraphLib.mk  $(BUILD_TYPE)) 
	(cd GraphTest; $(MAKE) -B -f GraphTest.mk $(BUILD_TYPE)) 