SUFFICES=.cu .cpp .h

AM_CPPFLAGS=-I$(top_srcdir) -I$(top_srcdir)/sqaodc -I$(top_srcdir)/3rdparty/eigen -I$(top_srcdir)/3rdparty/cub

LDADD=
LIBS=
LDFLAGS=

check_PROGRAMS=perf test dotval
perf_SOURCES=perf.cpp
dotval_SOURCES=dotval.cpp
test_SOURCES=main.cpp BFSearcherRangeCoverageTest.cpp CPUDenseGraphAnnealerTest.cpp CPUBipartiteGraphAnnealerTest.cpp MinimalTestSuite.cpp 

run: $(check_PROGRAMS)
	./test

# test for CUDA
if CUDA_ENABLED

test_SOURCES+=CUDAFormulasBGFuncTest.cpp CUDAFormulasDGFuncTest.cpp DeviceRandomTest.cpp CUDADenseGraphBFSolverTest.cpp DeviceSegmentedSumTest.cu CUDADenseGraphAnnealerTest.cpp CUDABipartiteGraphAnnealerTest.cpp utils.cpp DeviceMathTest.cpp DeviceTransform2dTest.cu DeviceTest.cpp

LDADD+=$(top_builddir)/sqaodc/libsqaodc_cuda.la
LDFLAGS+=-L$(CUDA_PREFIX)/lib64 -lcudart -ldl
#LDFLAGS+=@CUDA_LDFLAGS@ -lcublas -lcurand -lcudart

# CUDA build rules

# include ./$(DEPDIR)/DeviceSegmentedSumTest.Po

.cu.o:  # generate dep, and compile
	@mkdir -p $(DEPDIR)
	$(NVCC) -M -std=c++11 $(NVCCFLAGS) -expt-extended-lambda -Xcompiler "$(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CXXFLAGS) $(CXXFLAGS)" $<  -o $(DEPDIR)/$*.Tpo
	$(NVCC) -c -std=c++11 $(NVCCFLAGS) -expt-extended-lambda -Xcompiler "$(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CXXFLAGS) $(CXXFLAGS)"  $<  -o $*.o
	sed s/$*.o/$*.lo/ $(DEPDIR)/$*.Tpo > $(DEPDIR)/$*.Po
	rm -f $(DEPDIR)/$*.Tpo

# .cu.lo:
# 	mkdir -p .libs
# 	$(NVCC) -M -std=c++11 -arch=sm_61 -Xcompiler "$(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CXXFLAGS) $(CXXFLAGS)" $<  -o $(DEPDIR)/$*.Tpo  # generate dep
# 	$(NVCC) -c -std=c++11 -arch=sm_61 -Xcompiler "$(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CXXFLAGS) $(CXXFLAGS)"  $<  -o .libs/$*.o  # compile
# 	@echo "# Generated by libtool :  .lo file for CUDA objects." > $@
# 	@echo "pic_object='.libs/$*.o'" >> $@
# 	@echo "non_pic_object=none" >> $@ # FIXME: add static ver.
# 	sed s/$*.o/$*.lo/ $(DEPDIR)/$*.Tpo > $(DEPDIR)/$*.Plo
# 	rm -f $(DEPDIR)/$*.Tpo

%.Plo:
	touch $@
%.Po:
	touch $@

endif


LDADD+=$(top_builddir)/sqaodc/libsqaodc.la
#if WITH_BLAS
#  LIBS+=-lblas
#endif
#LIBS+=-ldl

