<?php

/**
 * Migrate Commerce products.
 */
class ImanimoFieldInventoryFieldCollections extends Migration {
  public $csvColumns = array(
    array('sku', 'SKU'),
    array('_title', 'Product'),
    array('_product_description', 'Description'),
    array('_commerce_price', 'Price'),
    array('_field_product_color', 'Color'),
    array('stock', 'Stock'),
    array('_field_images', 'Images'),
  );

  public $dependencies = array(
    'ImanimoProductSizeTerms',
    'ImanimoProductCommerceProducts',
  );

  public function __construct() {
    parent::__construct();

    $key = array(
      'sku' => array(
        'type' => 'varchar',
        'length' => 255,
        'not null' => TRUE,
      ),
    );
    $this->map = new MigrateSQLMap($this->machineName, $key, MigrateDestinationFieldCollection::getKeySchema());

    // Create a MigrateSource object.
    $this->source = new MigrateSourceCSV(drupal_get_path('module', 'imanimo_migrate') . '/csv/products.csv', $this->csvColumns, array('header_rows' => 1));
    $this->destination = new MigrateDestinationFieldCollection('field_inventory', array('host_entity_type' => 'commerce_product'));

    $this->addFieldMapping('host_entity_id', 'sku')
      ->sourceMigration('ImanimoProductCommerceProducts');

    $this
      ->addFieldMapping('field_product_size', 'stock')
      ->separator(',')
      ->sourceMigration('ImanimoProductSizeTerms');

    $this
      ->addFieldMapping('field_product_stock', 'stock')
      ->separator(',');
  }

  public function prepareRow($row) {
  }
}