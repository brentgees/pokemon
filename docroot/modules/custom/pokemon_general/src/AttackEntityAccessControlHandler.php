<?php

namespace Drupal\pokemon_general;

use Drupal\Core\Entity\EntityAccessControlHandler;
use Drupal\Core\Entity\EntityInterface;
use Drupal\Core\Session\AccountInterface;
use Drupal\Core\Access\AccessResult;

/**
 * Access controller for the Attack entity entity.
 *
 * @see \Drupal\pokemon_general\Entity\AttackEntity.
 */
class AttackEntityAccessControlHandler extends EntityAccessControlHandler {

  /**
   * {@inheritdoc}
   */
  protected function checkAccess(EntityInterface $entity, $operation, AccountInterface $account) {
    /** @var \Drupal\pokemon_general\Entity\AttackEntityInterface $entity */
    switch ($operation) {
      case 'view':
        if (!$entity->isPublished()) {
          return AccessResult::allowedIfHasPermission($account, 'view unpublished attack entity entities');
        }
        return AccessResult::allowedIfHasPermission($account, 'view published attack entity entities');

      case 'update':
        return AccessResult::allowedIfHasPermission($account, 'edit attack entity entities');

      case 'delete':
        return AccessResult::allowedIfHasPermission($account, 'delete attack entity entities');
    }

    // Unknown operation, no opinion.
    return AccessResult::neutral();
  }

  /**
   * {@inheritdoc}
   */
  protected function checkCreateAccess(AccountInterface $account, array $context, $entity_bundle = NULL) {
    return AccessResult::allowedIfHasPermission($account, 'add attack entity entities');
  }

}
