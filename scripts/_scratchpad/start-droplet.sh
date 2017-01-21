#!/bin/bash

hname=`gdate +%s%N`
echo "Creating droplet with name: $hname"

droplet_id=`curl -s -X POST              \
     -H "Content-Type: application/json" \
     -H "Authorization: Bearer $TOKEN"   \
     -d '{"name":"'$hname'",
          "region":"$REGION","size":"$SIZE",
          "image":"$IMAGE",
          "ssh_keys":["$SSH_FINGERPRINT"],
          "backups":false,"ipv6":false,"user_data":null,"private_networking":null}' \
     "https://api.digitalocean.com/v2/droplets" | jq .droplet.id`
echo "Droplet id: $droplet_id"

droplet_ip=`curl -s -X GET \
     -H "Content-Type: application/json" \
     -H "Authorization: Bearer $TOKEN"   \
     "https://api.digitalocean.com/v2/droplets/$droplet_id" | jq -r .droplet.networks.v4[0].ip_address`
echo "Droplet ip: $droplet_ip"
