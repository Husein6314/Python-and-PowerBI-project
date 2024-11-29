🏬 Super Store Data Warehouse
📊 Overview
Welcome to the Super Store Data Warehouse project! This project provides insights into sales, revenue, profit, and orders across different regions to support reporting and business decision-making.

🎯 Objective
To design a data warehouse that enables efficient reporting on key performance metrics, including:

Sales
Revenue
Profit
Order Quantities
📝 Business Problem
The Super Store business requires a consolidated view of its operations across various regions to make data-driven decisions. This data warehouse provides an overview of sales performance, helping the business track its progress and optimize strategies.

💾 Data Sources
Source Type: Flat files
File Format: CSV
Data Structure: Structured
🛠️ Architecture
The data warehouse follows a Star Schema design with the following layers:

Staging Layer: Raw data loaded from CSV files.
Core Layer: Cleaned and transformed data in star schema format.
Presentation Layer: Data prepared for reporting and dashboards.
🗂️ Schema Design
🔑 Fact Tables
factSales: Tracks sales transactions.
factReturns: Tracks product returns.
🛒 Dimension Tables
dimDate: Date and time attributes.
dimTerritory: Regional information.
dimCustomer: Customer details.
dimProducts: Product attributes.
🔗 Relationships:
Fact-to-Dimension Connections through primary and foreign keys to support complex queries.

🛠️ ETL Process
Tool Used: Pentaho Data Integration (PDI)

Stages:
Extract: Load data from CSV files.
Transform: Handle data type conversions, key mappings, and error handling.
Load: Populate staging and core layers in the MySQL database.
⚙️ Challenges Faced:
Data Type Mismatches: Resolved through data type transformations.
Relationship Constraints: Handled by pre-validating foreign keys before loading.
💾 Technology Stack
Database: MySQL
ETL Tool: Pentaho
Environment: On-premise
🚀 Performance Optimization
Indexes: Created on fact tables (SalesKey, CustomerKey, etc.) to improve query performance.
Optimized Joins: Between fact and dimension tables to reduce query execution time.
📊 Dashboards & Reporting
Key Metrics Tracked:
💰 Total Revenue
📈 Profit
👥 Customer Count
🛍️ Order Quantity
Report Types:
Pie Charts: Customer segmentation by region.
Bar Charts: Sales by product category.
Line Charts: Monthly revenue trends.
🔍 Entity-Relationship Diagram (ERD)
Here’s a simplified view of the schema design:

sql
Copy code
CREATE TABLE dimDate (
  DateKey INT PRIMARY KEY,
  Date DATE,
  Year INT,
  MonthName VARCHAR(20),
  DayName VARCHAR(20)
);

CREATE TABLE factSales (
  SalesKey INT AUTO_INCREMENT PRIMARY KEY,
  DateKey INT,
  ProductKey INT,
  CustomerKey INT,
  TerritoryKey INT,
  TotalPrice DECIMAL(10, 2),
  FOREIGN KEY (DateKey) REFERENCES dimDate(DateKey)
);
🛡️ Maintenance and Support
Backups:
Regular backups for staging and core layers.
Monitoring:
Data Quality Checks: Regular validation of data integrity, including completeness, consistency, and uniqueness.
ETL Monitoring: Track ETL job success/failure and log performance metrics, such as load times.
🎨 Project Highlights
Star Schema Design for optimized reporting.
Pentaho ETL for automated data integration.
MySQL for robust data storage.
Interactive Dashboards with KPIs like revenue and profit.
🤝 Contributions
Feel free to fork this repository and submit pull requests to improve the project! 😊

Monitoring and Data Quality
To ensure the reliability and accuracy of the data in the warehouse, the following monitoring and data quality checks are implemented:

Data Quality Checks:
Completeness: Ensure all necessary fields, like CustomerKey and ProductKey, are filled.
Consistency: Validate that all records in the sales table have matching entries in dimension tables.
Uniqueness: Ensure that keys such as SalesKey are unique across fact tables.
Range: Make sure values like TotalPrice are within expected ranges (i.e., no negative values).
Format: Check the format of data like dates and email addresses for consistency.
ETL Monitoring:
Track ETL job status (success or failure).
Set up error logging to capture data issues or system errors.
Implement automated alerts via email or Slack if ETL jobs fail.
By incorporating these practices, we ensure that the ETL process runs smoothly and that only valid data is included in the data warehouse.

