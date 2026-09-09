# Design Decisions

## Price representation

Prices are represented using signed integers rather than floating-point values.

Example:

10025 may represent €100.25 when the tick unit is one cent.

Reason:

Floating-point values can introduce rounding and equality-comparison issues.

Trade-off:

The system must define an explicit price scale or tick size.