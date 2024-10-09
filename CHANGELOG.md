# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [x.y.z] dd mm yyyy

### Added

### Changed
* Graph template now accepts Edge as type

### Deprecated

### Removed

### Fixed

## [0.0.2] 9 Oct 2024

### Added
* templates namespace. Implement Graph and Tree skeleton for reusable code (metaprogramming).
* lightweight namespace. Basic implementation of graph/digrapg/tree for critical performance UCs.
* Improved overall performance.
* Exhaustive testing.

### Changed
* Rename Tree to SmartTree
* Use non-virtual inheritance to avoid code duplication (previously using aggregation)

### Deprecated

### Removed
* Optional Node data. Now every node must hold a value. Notice this value could be an std::optional, but must be specified

### Fixed
* AddChild was crashing due to an invalid reference when resizing nodes vector.
* Tree was not properly initializing ougoting edges (ref to base class).

### Security

## [0.0.1] 5 Oct 2024

* FIRST RELEASE