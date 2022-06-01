# ParaGraph

## [](https://github.com/paragraph-sim/paragraph-core#disclaimer)Disclaimer

This is not an official Google product. This project was created by  [Michael Isaev](https://www.github.com/michael-isaev)  and  [Nic McDonald](https://www.github.com/nicmcd)  at Google.

## [](https://github.com/paragraph-sim/paragraph-core#what-is-it)What is it?

ParaGraph is a  _Para_llel  _Graph_  representation of parallel computing applications that can be executed in a system level simulator. ParaGraph is designed to be an interface between the parallel program source code, and a system level simulator that should "execute" the program on the model of a distributed system. You can think about ParaGraph as an IR (Intermediate Representation) that can be interfaced with various simulators as a backend, just similar to how LLVM IR or MLIR can be interfaced with backends that target various hardware. This approach allows us to introduce accurate application models to system level simulation frameworks, and model parallel computing applications execution on the future distributed systems.

## [](https://github.com/paragraph-sim/paragraph-core#how-it-works)How it works

Paragraph extracts high level computation and communication nodes from the compiled program or an execution trace, performs topology-based communication lowering, and rewrites the graph in the special format suitable for graph execution in a system simulator. Currently, we are targeting  [Tensorflow](https://github.com/tensorflow/tensorflowhttps://github.com/tensorflow/tensorflow)  and  [PyTorch](https://github.com/pytorch/pytorch)  programs through  [XLA compiler](https://github.com/tensorflow/tensorflow/tree/master/tensorflow/compiler/xla). MPI programs are planned to be supported in the future.

## [](https://github.com/paragraph-sim/paragraph-core#paragraph-origin)ParaGraph origin

Originally, ParaGraph was a summer 2020 internship project at Google that aimed to extract communication traffic from Machine Learning applications written in  [TensorFlow](https://github.com/tensorflow/tensorflowhttps://github.com/tensorflow/tensorflow), and simulate it in  [SuperSim](https://github.com/ssnetsim/supersim)  event driven network simulator.

## How to install
To install all the tools needed to to work with ParaGraph, you can use following bash script:
```
mkdir paragraph-sim; cd paragraph-sim
for prj in paragraph-core ho-bridge; do
  git clone git@github.com:paragraph-sim/${prj} ${prj}
  cd ${prj}
  bazel test -c opt ...
  cd ..
done
for prj in paragraph-creator hlo-examples; do
  git clone git@github.com:paragraph-sim/${prj} ${prj}
done
```
### Bazel
The C++ projects use [Bazel](https://bazel.build/ "Bazel Build") for building binaries. To install Bazel, follow the directions at [here](https://bazel.build/install "Bazel Install"). You need bazel-3.7.2.
Use the following command to build and test the project 
```
bazel test -c opt ...
```
### Spack
To install ParaGraph tools using [spack](https://github.com/spack/spack), follow the steps from the `build_with_spack_cmake.sh` script:
1. [Install spack](https://spack.readthedocs.io/en/latest/getting_started.html#installation)
2. Install [nicspack repository](https://github.com/nicmcd/nicspack)
3. Run paragraph building script
```
 ./build_with_spack_cmake.sh
```
### Cmake
We primarily use Bazel to build ParaGraph and its tools. However, if you want to build ParaGraph for you project using cmake, it is also possible. Please consult with [CMakeLists.txt](https://github.com/paragraph-sim/paragraph-core/blob/main/CMakeLists.txt "CMakeLists.txt"), [libparagraph.pc.in](https://github.com/paragraph-sim/paragraph-core/blob/main/libparagraph.pc.in "libparagraph.pc.in"), and [build_with_spack_cmake.sh](https://github.com/paragraph-sim/paragraph-core/blob/main/build_with_spack_cmake.sh "build_with_spack_cmake.sh").

## ParaGraph tools
In addition to the core library that can be used to add ParaGraph graph support to external simulators, `paragraph-core` repo provides several tools that can be used to build various flexible modeling workflows.
### graph_converter
[Graph converter](https://github.com/paragraph-sim/paragraph-core/blob/main/paragraph/graph/graph_converter.cc "graph_converter.cc") can be used to convert ParaGraph graph files between supported binary version `.pb` and  text version`.textproto`. It can also be used to add extra dependencies to the graph nodes and make every instruction execute sequentially in [post order traversal](https://en.wikipedia.org/wiki/Tree_traversal#Post-order,_LRN) using flag `--enforce_postorder`.
To build graph converter, type
```
bazel build -c opt paragraph/graph:graph_converter
 ```
To see helpline with information about flags and how to use it, type
```
bazel-bin/paragraph/graph/graph_converter --help
```
### graph_data_parallel_extender
[Graph data parallel extender](https://github.com/paragraph-sim/paragraph-core/blob/main/paragraph/graph/graph_data_parallel_extender.cc "graph_data_parallel_extender.cc") helps to change the system size for the given input graph. It only works with graphs that correspond to neural networks workloads that only utilize data parallelism.
To build graph data parallel extender, type
```
bazel build -c opt paragraph/graph:graph_data_parallel_extender
 ```
To see helpline with information about flags and how to use it, type
```
bazel-bin/paragraph/graph/graph_data_parallel_extender --help
```
### graph_translator
[Graph translator](https://github.com/paragraph-sim/paragraph-core/blob/main/paragraph/translation/graph_translator.cc "graph_translator.cc") performs a graph translation according to `translation_config.json` file. Translation process helps to rewrite a graph for a particular simulator by substituting instructions that simulator doesn't understand with new instruction sequences that only have instructions supported by simulators. 
To build graph translator, type
```
bazel build -c opt paragraph/translation:graph_translator
 ```
To see helpline with information about flags and how to use it, type
```
bazel-bin/paragraph/translation/graph_translator --help
```
### simulator
[Simulator](https://github.com/paragraph-sim/paragraph-core/blob/main/paragraph/simulator/simulator.cc "simulator.cc") implements a simple analytical model that can "execute" the provided graph. It is useful for graph debugging and testing, as well as for fast performance prediction of graph execution time using a simple [roofline](https://en.wikipedia.org/wiki/Roofline_model) analytical model for both computation and communication.
To build simulator, type
```
bazel build -c opt paragraph/simulator/simulator
 ```
To see helpline with information about flags and how to use it, type
```
bazel-bin/paragraph/simulator/simulator --help
```
## ParaGraph workflow
ParaGraph can be used to build flexible modeling workflow. It is totally up to each user to pick the right tools and the necessary steps to support their needs. Here we show an example of one of the possible modeling workflows one could build using open-source tools currently supported by ParaGraph:
1. Get a graph by using [paragraph-creator](https://github.com/paragraph-sim/paragraph-creator) or translating an XLA HLO graph using [hlo-bridge](https://github.com/paragraph-sim/hlo-bridge).
2. Translate a graph using [graph translator](https://github.com/paragraph-sim/paragraph-core/blob/main/paragraph/translation/graph_translator.cc "graph_translator.cc") for your simulator, e.g. to use a particular [`all-reduce` algorithm](https://github.com/paragraph-sim/paragraph-core/tree/main/paragraph/translation/allreduce). 
3. Run graph application modeling in a simulator, for example [SuperSim](https://github.com/ssnetsim/supersim)

You can also take a look at [paragraph-scripts](https://github.com/paragraph-sim/paragraph-scripts) repo with useful scripts and translation config examples.
## How to cite
The ParaGraph paper is under review, we will update this section once itt is accepted.
