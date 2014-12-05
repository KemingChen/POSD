rmdir CppCoverageReport-ProductionCode /s /q
OpenCppCoverage --source MindMapGUI --output CppCoverageReport-ProductionCode --excluded_sources TestMindMap -- Debug\TestMindMap.exe 
start CppCoverageReport-ProductionCode/index.html