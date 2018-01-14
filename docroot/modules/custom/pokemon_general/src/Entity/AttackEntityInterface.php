<?php

namespace Drupal\pokemon_general\Entity;

use Drupal\Core\Entity\ContentEntityInterface;
use Drupal\Core\Entity\EntityChangedInterface;
use Drupal\user\EntityOwnerInterface;

/**
 * Provides an interface for defining Attack entity entities.
 *
 * @ingroup pokemon_general
 */
interface AttackEntityInterface extends  ContentEntityInterface, EntityChangedInterface, EntityOwnerInterface {

  // Add get/set methods for your configuration properties here.

  /**
   * Gets the Attack entity name.
   *
   * @return string
   *   Name of the Attack entity.
   */
  public function getName();

  /**
   * Sets the Attack entity name.
   *
   * @param string $name
   *   The Attack entity name.
   *
   * @return \Drupal\pokemon_general\Entity\AttackEntityInterface
   *   The called Attack entity entity.
   */
  public function setName($name);

  /**
   * Gets the Attack entity creation timestamp.
   *
   * @return int
   *   Creation timestamp of the Attack entity.
   */
  public function getCreatedTime();

  /**
   * Sets the Attack entity creation timestamp.
   *
   * @param int $timestamp
   *   The Attack entity creation timestamp.
   *
   * @return \Drupal\pokemon_general\Entity\AttackEntityInterface
   *   The called Attack entity entity.
   */
  public function setCreatedTime($timestamp);

  /**
   * Returns the Attack entity published status indicator.
   *
   * Unpublished Attack entity are only visible to restricted users.
   *
   * @return bool
   *   TRUE if the Attack entity is published.
   */
  public function isPublished();

  /**
   * Sets the published status of a Attack entity.
   *
   * @param bool $published
   *   TRUE to set this Attack entity to published, FALSE to set it to unpublished.
   *
   * @return \Drupal\pokemon_general\Entity\AttackEntityInterface
   *   The called Attack entity entity.
   */
  public function setPublished($published);

}
