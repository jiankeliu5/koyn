#include "Koyn.h"

uint32_t ElectrumRequestData::reqId=0;

ElectrumRequestData::ElectrumRequestData()
{
	localReqId=reqId++;
	reqType=0;
	dataInt = -1;
	isUsed = false;
}

void ElectrumRequestData::setReqType(uint32_t bitShift)
{
	reqType |= (0x01<<bitShift);
}

void ElectrumRequestData::setUsed()
{
	isUsed = true;
}

void ElectrumRequestData::resetUsed()
{
	isUsed = false;
}

bool ElectrumRequestData::isReqUsed()
{
	return isUsed;
}

uint32_t ElectrumRequestData::getReqId()
{
	return localReqId;
}

uint32_t ElectrumRequestData::getReqType()
{
	return reqType;
}

uint8_t * ElectrumRequestData::getDataString()
{
	return dataString;
}

uint32_t ElectrumRequestData::getDataInt()
{
	return dataInt;
}

/************************************************** ElectrumRequestsClassClass *******************************************************/
ElectrumRequests::ElectrumRequests()
{
}


void ElectrumRequests::sendVersion()
{
	for(int i = 0;i<MAX_CONNECTED_SERVERS;i++)
	{
		if(Koyn.getClient(i)->connected())
		{
			ElectrumRequestData  * currentReq = ElectrumRequests::getElectrumRequestData();
			if(currentReq)
			{
				Koyn.getClient(i)->print(String(jsonMessage.createJsonMessageString(currentReq->getReqId(),"server.version",VERSION_STRING))+"\n");
				currentReq->setReqType(VERSION_BIT);
				currentReq->setUsed();
				aJson.deleteItem(jsonMessage.versionMessage);
				free(jsonMessage.json);
			}
		}
	}
}

void ElectrumRequests::subscribeToPeers()
{
	for(int i = 0;i<MAX_CONNECTED_SERVERS;i++)
	{
		if(Koyn.getClient(i)->connected())
		{
			int32_t param= -1;
			ElectrumRequestData  * currentReq = ElectrumRequests::getElectrumRequestData();
			if(currentReq)
			{
				Koyn.getClient(i)->print(String(jsonMessage.createJsonMessage(currentReq->getReqId(),"server.peers.subscribe",&param))+"\n");
				currentReq->setReqType(PEERS_SUBS_BIT);
				currentReq->setUsed();
				aJson.deleteItem(jsonMessage.versionMessage);
				free(jsonMessage.json);
			}
		}
	}
}

void ElectrumRequests::subscribeToBlocksNumber()
{
	if(Koyn.getMainClient()&&Koyn.getMainClient()->connected())
	{
		int32_t param= -1;
		ElectrumRequestData * currentReq = ElectrumRequests::getElectrumRequestData();
		if(currentReq)
		{
			Koyn.getMainClient()->print(String(jsonMessage.createJsonMessage(currentReq->getReqId(),"blockchain.numblocks.subscribe",&param))+"\n");
			currentReq->setReqType(BLOCKS_NO_SUBS_BIT);
			currentReq->setUsed();
			aJson.deleteItem(jsonMessage.versionMessage);
			free(jsonMessage.json);
		}
	}
}


void ElectrumRequests::subscribeToBlockHeaders()
{
	for(int i = 0;i<MAX_CONNECTED_SERVERS;i++)
	{
		if(Koyn.getClient(i)->connected())
		{
			int32_t param = -1;
			ElectrumRequestData * currentReq = ElectrumRequests::getElectrumRequestData();
			if(currentReq)
			{
				Koyn.getClient(i)->print(String(jsonMessage.createJsonMessage(currentReq->getReqId(),"blockchain.headers.subscribe",&param))+"\n");
				currentReq->setReqType(HEADERS_SUBS_BIT);
				currentReq->setUsed();
				aJson.deleteItem(jsonMessage.versionMessage);
				free(jsonMessage.json);
			}
		}
	}
}

void ElectrumRequests::subscribeToAddress(const char  * address)
{
	if(Koyn.getMainClient()&&Koyn.getMainClient()->connected())
	{
		ElectrumRequestData * currentReq = ElectrumRequests::getElectrumRequestData();
		if(currentReq)
		{
			Koyn.getMainClient()->print(String(jsonMessage.createJsonMessageString(currentReq->getReqId(),"blockchain.address.subscribe",address))+"\n");
			currentReq->setReqType(ADDRESS_SUBS_BIT);
			currentReq->setUsed();
			memcpy(currentReq->dataString,address,strlen(address));
			aJson.deleteItem(jsonMessage.versionMessage);
			free(jsonMessage.json);
		}
	}
}

void ElectrumRequests::getAddressHistory(const char  * address)
{
	if(Koyn.getMainClient()&&Koyn.getMainClient()->connected())
	{
		ElectrumRequestData * currentReq = ElectrumRequests::getElectrumRequestData();
		if(currentReq)
		{
			Koyn.getMainClient()->print(String(jsonMessage.createJsonMessageString(currentReq->getReqId(),"blockchain.address.get_history",address))+"\n");
			currentReq->setReqType(ADRRESS_HISTORY_BIT);
			currentReq->setUsed();
			memcpy(currentReq->dataString,address,strlen(address));
			aJson.deleteItem(jsonMessage.versionMessage);
			free(jsonMessage.json);
		}
	}
}

void ElectrumRequests::getAddressBalance(const char  * address)
{
	if(Koyn.getMainClient()&&Koyn.getMainClient()->connected())
	{
		ElectrumRequestData * currentReq = ElectrumRequests::getElectrumRequestData();
		if(currentReq)
		{
			Koyn.getMainClient()->print(String(jsonMessage.createJsonMessageString(currentReq->getReqId(),"blockchain.address.get_balance",address))+"\n");
			currentReq->setReqType(ADDRESS_BALANCE_BIT);
			currentReq->setUsed();
			memcpy(currentReq->dataString,address,strlen(address));
			aJson.deleteItem(jsonMessage.versionMessage);
			free(jsonMessage.json);
		}
	}
}

void ElectrumRequests::getMempool(const char  * address)
{
	if(Koyn.getMainClient()&&Koyn.getMainClient()->connected())
	{
		ElectrumRequestData * currentReq = ElectrumRequests::getElectrumRequestData();
		if(currentReq)
		{
			Koyn.getMainClient()->print(String(jsonMessage.createJsonMessageString(currentReq->getReqId(),"blockchain.address.get_mempool",address))+"\n");
			currentReq->setReqType(ADDRESS_MEMPOOL_BIT);
			currentReq->setUsed();
			// memcpy(currentReq->dataString,address,strlen(address));
			aJson.deleteItem(jsonMessage.versionMessage);
			free(jsonMessage.json);
		}
	}
}

void ElectrumRequests::getMerkleProof(const char * address,const char  * txHash,int height)
{
	if(Koyn.getMainClient()&&Koyn.getMainClient()->connected())
	{
		ElectrumRequestData * currentReq = ElectrumRequests::getElectrumRequestData();
		if(currentReq)
		{
			Koyn.getMainClient()->print(String(jsonMessage.createJsonMessage(currentReq->getReqId(),"blockchain.transaction.get_merkle",txHash,&height))+"\n");
			currentReq->setReqType(MERKLE_PROOF);
			currentReq->setUsed();
			memcpy(currentReq->dataString,address,strlen(address));
			aJson.deleteItem(jsonMessage.versionMessage);
			free(jsonMessage.json);
		}
	}
}

void ElectrumRequests::getBlockHeader(int blockHeight)
{
	for(int i = 0;i<MAX_CONNECTED_SERVERS;i++)
	{
		if(Koyn.getClient(i)->connected())
		{
			ElectrumRequestData  * currentReq = ElectrumRequests::getElectrumRequestData();
			if(currentReq)
			{
				Koyn.getClient(i)->print(String(jsonMessage.createJsonMessage(currentReq->getReqId(),"blockchain.block.get_header",&blockHeight))+"\n");
				currentReq->setReqType(BLOCK_HEADER_BIT);
				currentReq->setUsed();
				currentReq->dataInt = blockHeight;
				aJson.deleteItem(jsonMessage.versionMessage);
				free(jsonMessage.json);
			}
		}
	}
}

void ElectrumRequests::listUtxo(const char  * address)
{
	if(Koyn.getMainClient()&&Koyn.getMainClient()->connected())
	{
		ElectrumRequestData * currentReq = ElectrumRequests::getElectrumRequestData();
		if(currentReq)
		{
			Koyn.getMainClient()->print(String(jsonMessage.createJsonMessageString(currentReq->getReqId(),"blockchain.address.listunspent",address))+"\n");
			currentReq->setReqType(ADDRESS_UTXO_BIT);
			currentReq->setUsed();
			memcpy(currentReq->dataString,address,strlen(address));
			aJson.deleteItem(jsonMessage.versionMessage);
			free(jsonMessage.json);
		}
	}
}


void ElectrumRequests::getBlockChunks(int clientNo)
{
	if(Koyn.getClient(clientNo)->connected()&&Koyn.noOfChunksNeeded)
	{
		ElectrumRequestData  * currentReq = ElectrumRequests::getElectrumRequestData();
		if(currentReq)
		{
			Koyn.getClient(clientNo)->print(String(jsonMessage.createJsonMessage(currentReq->getReqId(),"blockchain.block.get_chunk",(int32_t*)&Koyn.chunkNo))+"\n");
			currentReq->setReqType(BLOCK_CHUNKS_BIT);
			currentReq->setUsed();
			aJson.deleteItem(jsonMessage.versionMessage);
			free(jsonMessage.json);
		}
	}
}


void ElectrumRequests::relayFee()
{
	if(Koyn.getMainClient()&&Koyn.getMainClient()->connected())
	{
		int param= -1;
		ElectrumRequestData * currentReq = ElectrumRequests::getElectrumRequestData();
		if(currentReq)
		{
			Koyn.getMainClient()->print(String(jsonMessage.createJsonMessage(currentReq->getReqId(),"blockchain.estimatefee",&param))+"\n");
			currentReq->setReqType(RELAY_FEE_BIT);
			currentReq->setUsed();
			aJson.deleteItem(jsonMessage.versionMessage);
			free(jsonMessage.json);
		}
	}
}


void ElectrumRequests::broadcastTransaction(File * transactionFile)
{
	if(Koyn.getMainClient()&&Koyn.getMainClient()->connected())
	{
		ElectrumRequestData * currentReq = ElectrumRequests::getElectrumRequestData();
		if(currentReq)
		{
			Koyn.getMainClient()->print(String("{\"id\":")+String(currentReq->getReqId()));
			Koyn.getMainClient()->print(",\"method\":\"blockchain.transaction.broadcast\",\"params\":[\"");
			while(transactionFile->available()){Koyn.getMainClient()->write(transactionFile->read());}
			Koyn.getMainClient()->print("\"]}\n");
			currentReq->setReqType(BROADCAST_TRANSACTION_BIT);
			currentReq->setUsed();
		}
	}
}

void ElectrumRequests::getTransaction(const char * txHash)
{
	if(Koyn.getMainClient()&&Koyn.getMainClient()->connected())
	{
		ElectrumRequestData * currentReq = ElectrumRequests::getElectrumRequestData();
		if(currentReq)
		{
			Koyn.getMainClient()->print(String(jsonMessage.createJsonMessageString(currentReq->getReqId(),"blockchain.transaction.get",txHash))+"\n");
			currentReq->setReqType(TRANSACTION_BIT);
			currentReq->setUsed();
			// memcpy(currentReq->dataString,address,strlen(address));
			aJson.deleteItem(jsonMessage.versionMessage);
			free(jsonMessage.json);
		}
	}
}


ElectrumRequestData * ElectrumRequests::getElectrumRequestData()
{
	int i=0;
	while(i<MAX_PARALLEL_REQUESTS)
	{
		if(!electrumRequestDataArray[i].isReqUsed())
		{
			return &electrumRequestDataArray[i];
		}
		i++;
	}
	return NULL;
}

ElectrumRequestData * ElectrumRequests::getElectrumRequestData(unsigned int reqNo)
{
	int i=0;
	while(i<MAX_PARALLEL_REQUESTS)
	{
		if(electrumRequestDataArray[i].getReqId()== reqNo)
		{
			return &electrumRequestDataArray[i];
		}
		i++;
	}
	return NULL;
}

void ElectrumRequests::resetRequests()
{
	for(int i=0;i<MAX_PARALLEL_REQUESTS;i++)
	{
		electrumRequestDataArray[i].resetUsed();
	}
}
