/**
 * This software is distributed under the terms of the MIT License.
 * Copyright (c) 2020-2023 LXRobotics.
 * Author: Alexander Entinger <alexander.entinger@lxrobotics.com>
 * Contributors: https://github.com/107-systems/107-Arduino-Cyphal/graphs/contributors.
 */

#ifndef INC_107_ARDUINO_CYPHAL_SUBSCRIPTION_HPP
#define INC_107_ARDUINO_CYPHAL_SUBSCRIPTION_HPP

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <memory>

#include "CanardSubscription.h"

#include "libcanard/canard.h"

/**************************************************************************************
 * FORWARD DECLARATION
 **************************************************************************************/

class Node;

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace impl
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class SubscriptionBase : public CanardSubscription
{
public:
  SubscriptionBase() : CanardSubscription{CanardTransferKindMessage} { }
};

template <typename T, typename OnReceiveCb>
class Subscription : public SubscriptionBase
{
public:
  Subscription(Node & node_hdl, CanardPortID const port_id, OnReceiveCb const & on_receive_cb)
  : SubscriptionBase{}
  , _node_hdl{node_hdl}
  , _port_id{port_id}
  , _on_receive_cb{on_receive_cb}
  { }
  virtual ~Subscription();


  virtual bool onTransferReceived(CanardRxTransfer const & transfer) override;


private:
  Node & _node_hdl;
  CanardPortID const _port_id;
  OnReceiveCb _on_receive_cb;
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* impl */

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

using Subscription = std::shared_ptr<impl::SubscriptionBase>;

/**************************************************************************************
 * TEMPLATE IMPLEMENTATION
 **************************************************************************************/

#include "Subscription.ipp"

#endif /* INC_107_ARDUINO_CYPHAL_SUBSCRIPTION_HPP */
